#include <assert.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>

#include "trees.h"
#include "random.h"
#include "cmdline.h"

using namespace cmdline;

bool load_input_file(const string_t filename, string_list_t& string_list);

template <class TreeType>
void run(TreeType tree, const string_t name, const cmdline_options_t& options, string_list_t& string_list);

template <class TreeType>
void simulate(TreeType tree, const simulation_options_t options, const string_list_t& string_list);


int main(int argc, char* argv[]) {
	string_list_t list;
	cmdline_options_t options;

	if (argc == 1) {
		usage();
		return 1;
	}

	if (!parse(argc, argv, options)) {
		return 1;
	}

	if (!load_input_file(options.filename, list)) {
		printf("can't load '%s'\n", options.filename.c_str());
		return 1;
	}

	HashedTree<Fnv32> tree_fnv;
	HashedTreeEarlyRotate<Fnv32> tree_fnv_early_rotate;
	OneLevelTrie<Fnv32, 4> one_level_trie;
	BST bst;
	StlMapAdapter stl;

	run<BST>(bst, "BST", options, list);
	run<HashedTree<Fnv32> >(tree_fnv, "Hash (FNV32)", options, list);
	run<HashedTreeEarlyRotate<Fnv32> >(tree_fnv_early_rotate, "Hash (FNV32) with early rotate", options, list);
	//run<OneLevelTrie<Fnv32, 4> >(one_level_trie, "One level trie (FNV32)", options, list);
	run<StlMapAdapter>(stl, "STL map", options, list);

	return 0;
}


bool load_input_file(const string_t filename, string_list_t& string_list) {
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.is_open()) {
		return false; 
	}

	while (std::getline(file, line)) {
		string_list.push_back(line);
	}

	file.close();

	return true;
}


template <class TreeType>
void run(TreeType tree, const string_t name, const cmdline_options_t& options, string_list_t& string_list) {
	const char* c_name = name.c_str();

	if (options.verify) {
		printf("checking tree implementation %s:\n", c_name);
		puts("inserting values...");
			for (int i=0; i < string_list.size(); i++) {
				tree.insert(string_list[i]);
			}
		puts("... ok");

		puts("veryfing...");
			bool ok = true;
			for (int i=0; i < string_list.size(); i++) {
				if (!tree.find(string_list[i])) {
					printf("ERROR: '%s' not found\n", string_list[i].c_str());
					ok = false;
				}
			}

		if (ok)
			puts("... ok");

		return;
	}

	printf("tree implementation %s:\n", c_name);
	simulate<TreeType>(tree, options.simulation_options, string_list);
}


unsigned gettime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return (tv.tv_sec * 1000000 + tv.tv_usec)/1000;
}


template <class TreeType>
void simulate(TreeType tree, const simulation_options_t options, const string_list_t& string_list) {
	const size_t n = string_list.size();
	size_t i = 0;

	int inserts = 0;
	int finds   = 0;
	int steps;
	unsigned t1, t2;

	random::init(options.seed);

	steps = options.steps;
	t1 = gettime();
	while (steps--) {
		// TODO: add to simulation options
		if (random::next() % 100 > 50) {
			tree.insert(string_list[i]);
			inserts += 1;
		} else {
			tree.find(string_list[i]);
			finds += 1;
		}

		i++;
		if (n == i) i = 0;
	}
	t2 = gettime();

	printf("inserts: %d\n", inserts);
	printf("  finds: %d\n", finds);
	printf("   time: %u ms\n", t2 - t1);
}

