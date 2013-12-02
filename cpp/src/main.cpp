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

	if (options.trees.count("bst")) {
		typedef BST Tree;
		const string_t name = "BST";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("fnv32")) {
		typedef HashedTree<Fnv32> Tree;
		const string_t name = "Hash (FNV32)";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("earlyrotate")) {
		typedef HashedTreeEarlyRotate<Fnv32> Tree;
		const string_t name = "Hash (FNV32) with early rotate";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-3")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 3> Tree;
		const string_t name = "One level trie - 3 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-4")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 4> Tree;
		const string_t name = "One level trie - 4 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-6")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 6> Tree;
		const string_t name = "One level trie - 6 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-8")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 8> Tree;
		const string_t name = "One level trie - 8 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-10")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 10> Tree;
		const string_t name = "One level trie - 10 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-12")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 12> Tree;
		const string_t name = "One level trie - 12 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-14")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 14> Tree;
		const string_t name = "One level trie - 14 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-16")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 16> Tree;
		const string_t name = "One level trie - 16 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-hashed-18")) {
		typedef HashedTree<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 18> Tree;
		const string_t name = "One level trie - 18 bits [hashed tree (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-3")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 3> Tree;
		const string_t name = "One level trie - 3 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-4")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 4> Tree;
		const string_t name = "One level trie - 4 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-6")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 6> Tree;
		const string_t name = "One level trie - 6 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-8")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 8> Tree;
		const string_t name = "One level trie - 8 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-10")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 10> Tree;
		const string_t name = "One level trie - 10 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-12")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 12> Tree;
		const string_t name = "One level trie - 12 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-14")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 14> Tree;
		const string_t name = "One level trie - 14 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-16")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 16> Tree;
		const string_t name = "One level trie - 16 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("forest-earlyrotate-18")) {
		typedef HashedTreeEarlyRotate<Fnv32> HashedTreeType;
		typedef OneLevelTrie<HashedTreeType, 18> Tree;
		const string_t name = "One level trie - 18 bits [earlyrotate (FNV32)]";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("map")) {
		typedef StlMapAdapter Tree;
		const string_t name = "STL map";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

	if (options.trees.count("unordered_map")) {
		typedef StlUnorderedMapAdapter Tree;
		const string_t name = "STL unordered map";
		Tree tree;

		run<Tree>(tree, name, options, list);
	}

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

	lcg::init(options.seed);

	steps = options.steps;
	t1 = gettime();
	while (steps--) {
		if (lcg::next() % 100 > options.insert_probability) {
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

