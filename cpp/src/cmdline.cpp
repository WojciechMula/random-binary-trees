#include <algorithm>
#include <string>
#include <stdio.h>
#include "cmdline.h"


namespace cmdline {

void usage() {
	puts(
		"-f FILE            source file\n"
		"-t TREE            tree kind\n"
		"--hash NAME        hash name (when needed by -t)\n"
		"--bits COUNT       bits for options '-t forest-hashed'\n"
		"--sim-steps        count of simulation steps\n"
		"--sim-seed         initial seed for pseudo-random source\n"
		"--sim-insert-prob  probability of insert operation during simulation [0..100]\n"
		"-v                 verbose"
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
bool get_required_argument(string_list_t& items, const string_t value, string_t& argument);

bool parse_simulation(string_list_t& items, simulation_options_t& options);
bool parse_structure(string_list_t& items, options_t& options);
hash_kind_t parse_hash(string_list_t& items);
int parse_forest_bits(string_list_t& items);


bool parse(int argc, char* argv[], options_t& options) {
	string_list_t items;

	for (int i=1; i < argc; i++)
		items.push_back(argv[i]);

	if (FlagPresent == get_flag(items, "-h")) {
		usage();
		return false;
	}

	options.verify = (FlagPresent == get_flag(items, "--verify"));
	options.verbose = (FlagPresent == get_flag(items, "-v"));

	if (!get_required_argument(items, "-f", options.filename))
		return false;

	if (!parse_structure(items, options))
		return false;

	if (!parse_simulation(items, options.simulation_options))
		return false;

	if (!items.empty()) {
		puts("following options were not recognized");
		for (size_t i=0; i < items.size(); i++)
			printf("- '%s'\n", items[i].c_str());

		return false;
	}

	return true;
}


string_t structure_name(const options_t& options) {
	string_t result;

	switch (options.structure) {
		case BST:
			result = "BST";
			break;

		case STL_Map:
			result = "stl::map";
			break;

		case STL_Unordered_Map:
			result = "stl::unordered_map";
			break;
			
		case HashedTree:
			result = "Hashed BST";
			break;

		case HashedTreeEarlyRotate:
			result = "Hashed BST with early rotate";
			break;

		case ForestOfHashedTrees:
			result = "Forest of hashed BSTs";
			break;
	}

	if (options.hash != None || options.forest_bits > 0) {
		result = result + " (";
		switch (options.hash) {
			case FNV:
				result += "hash=FNV";
				break;

			case Murmur:
				result += "hash=Murmur";
				break;

			case None:
				break;
		}

		if (options.forest_bits > 0) {
			result += string_t(", bits=") + std::to_string(options.forest_bits);
		}

		result = result + ")";
	}

	return result;
}


bool parse_structure(string_list_t& items, options_t& options) {
	string_t name;

	switch (get_argument(items, "-t", name)) {
		case ArgumentMissing:
			puts("argument for option -t is required");
			return false;

		case FlagMissing:
			puts("argument -t is required");
			return false;
	}

	if (name == "bst") {
		options.structure = BST;
	} else
	if (name == "map") {
		options.structure = STL_Map;
	} else
	if (name == "unordered_map") {
		options.structure = STL_Unordered_Map;
	} else
	if (name == "hashedtree") {
		options.structure = HashedTree;
		options.hash = parse_hash(items);
		if (options.hash == None) {
			return false;
		}
	} else
	if (name == "hashedtree-earlyrotate") {
		options.structure = HashedTreeEarlyRotate;
		options.hash = parse_hash(items);
		if (options.hash == None) {
			return false;
		}
	} else
	if (name == "forest-hashed") {
		options.structure = ForestOfHashedTrees;
		options.hash = parse_hash(items);
		if (options.hash == None)
			return false;

		options.forest_bits = parse_forest_bits(items);
		if (options.forest_bits <= 0)
			return false;

	} else {
		printf("value '%s' for option -t is not valid, available values are:\n", name.c_str());
		puts("\tbst");
		puts("\tmap");
		puts("\tunordered_map");
		puts("\thashedtree");
		puts("\thashedtree-earlyrotate");
		puts("\tforest-hashed");

		return false;
	}

	return true;
}

hash_kind_t parse_hash(string_list_t& items) {
	string_t name;

	if (!get_required_argument(items, "--hash", name)) {
		return None;
	}

	if (name == "fnv") {
		return FNV;
	} else
	if (name == "murmur") {
		return Murmur;
	} else {
		printf("value '%s' for option --hash, available values are:\n", name.c_str());
		puts("\tfnv");
		puts("\tmurmur");

		return None;
	}
}


int parse_forest_bits(string_list_t& items) {
	string_t tmp;

	if (!get_required_argument(items, "--bits", tmp)) {
		return None;
	}

	const int val = atoi(tmp.c_str());
	switch (val) {
		case 3:
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:
		case 16:
		case 18:
			return val;

		default:
			printf("option --bits: value %d is not valid, available values:\n", val);
			puts("\t3, 4, 6, 8, 10, 12, 14, 16, 18");

			return 0;
	}
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
			items.erase(flag);

			return ArgumentMissing;
		}
	} else {
		return FlagMissing;
	}
}

bool get_required_argument(string_list_t& items, const string_t value, string_t& argument) {
	switch (get_argument(items, value, argument)) {
		case FlagPresent:
			return true;

		case FlagMissing:
			printf("option %s is required\n", value.c_str());

			return false;

		case ArgumentMissing:
			printf("value for option %s missing\n", value.c_str());

			return false;
	}

	return false;
}

} // namespace
