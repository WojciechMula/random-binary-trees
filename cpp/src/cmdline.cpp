#include <algorithm>
#include <stdio.h>
#include "cmdline.h"


namespace cmdline {

void usage() {
	puts(
		"-f FILE            source file\n"
		"-t TREES           list of tree names\n"
		"--sim-steps        count of simulation steps\n"
		"--sim-seed         initial seed for pseudo-random source\n"
		"--sim-insert-prob  probability of insert operation during simulation [0..100]\n"
		"--verify\n"
	);
}

typedef enum {
	FlagMissing,
	FlagPresent,
	ArgumentMissing
} argument_state_t;

argument_state_t get_flag(string_list_t& items, const string_t value);
int get_argument(string_list_t& items, const string_t value, string_t& argument);
bool parse_simulation(string_list_t& items, simulation_options_t& options);
bool parse_tree_list(string_list_t& items, cmdline_options_t& options);
size_t split(const string_t string, string_list_t& list);


bool parse(int argc, char* argv[], cmdline_options_t& options) {
	string_list_t items;

	for (int i=1; i < argc; i++)
		items.push_back(argv[i]);

	if (FlagPresent == get_flag(items, "-h")) {
		usage();
		return false;
	}

	options.verify = (FlagPresent == get_flag(items, "--verify"));

	switch (get_argument(items, "-f", options.filename)) {
		case FlagMissing:
			puts("option -f is required");
			return false;

		case ArgumentMissing:
			puts("argument for option -f is required");
			return false;
	}

	if (!parse_simulation(items, options.simulation_options)) {
		return false;
	}

	if (!parse_tree_list(items, options)) {
		return false;
	}

	if (!items.empty()) {
		puts("following options were not recoginzed");
		for (int i=0; i < items.size(); i++) {
			printf("- '%s'\n", items[i].c_str());
		}

		return false;
	}

	return true;
}

bool parse_simulation(string_list_t& items, simulation_options_t& options) {
	string_t tmp;

	switch (get_argument(items, "--sim-steps", tmp)) {
		case ArgumentMissing:
			puts("argument for option --sim-steps is required");
			return false;

		case FlagPresent:
			options.steps = atoi(tmp.c_str());
			break;
	}

	switch (get_argument(items, "--sim-seed", tmp)) {
		case ArgumentMissing:
			puts("argument for option --sim-seed is required");
			return false;

		case FlagPresent:
			options.seed = atoi(tmp.c_str());
			break;
	}

	switch (get_argument(items, "--sim-insert-prob", tmp)) {
		case ArgumentMissing:
			puts("argument for option --sim-insert-prob is required");
			return false;

		case FlagPresent:
			options.insert_probability = atoi(tmp.c_str());
			if (options.insert_probability < 0 || options.insert_probability > 100) {
				puts("value for option --sim-insert-prob must be in range [0..100]");
				return false;
			}
			break;
	}

	return true;
}

bool parse_tree_list(string_list_t& items, cmdline_options_t& options) {
	string_t tmp, name;

	switch (get_argument(items, "-t", tmp)) {
		case ArgumentMissing:
			puts("argument for option -t is required");
			return false;

		case FlagMissing:
			options.use_all_trees();
			return true;
	}

	string_list_t list;

	size_t n = split(tmp, list);
	if (n > 0) {
		for (size_t i = 0; i < n; i++) {
			if (!options.use_tree(list[i])) {
				printf("tree '%s' is unknown, available names:\n", list[i].c_str());
				for (auto it = options.all_trees.begin(); it != options.all_trees.end(); ++it) {
					printf("- '%s'\n", (*it).c_str());
				}

				return false;
			}
		}
	} else
		options.use_all_trees();

	return true;
}


size_t split(const string_t string, string_list_t& list) {
	size_t start = 0;
	size_t end   = string.find(',');
	while (end != string_t::npos) {
		list.push_back(string.substr(start, end - start));

		start = end + 1;
		end = string.find(',', start);
	}

	list.push_back(string.substr(start, end - start));

	return list.size();
}


argument_state_t get_flag(string_list_t& items, const string_t value) {
	const string_list_t::iterator it = std::find(items.begin(), items.end(), value);

	if (it != items.end()) {
		items.erase(it);
		
		return FlagPresent;
	} else {
		return FlagMissing;
	}
}

int get_argument(string_list_t& items, const string_t value, string_t& argument) {
	string_list_t::iterator flag = std::find(items.begin(), items.end(), value);

	if (flag != items.end()) {
		string_list_t::iterator arg = flag + 1;

		if (arg != items.end()) {
			argument = *arg;
			items.erase(flag, arg + 1);

			return FlagPresent;
		} else {
			items.erase(arg);

			return ArgumentMissing;
		}
	} else {
		return FlagMissing;
	}
}

} // namespace
