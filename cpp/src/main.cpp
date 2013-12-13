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

bool load_input_file(const string_t filename, string_list_t& string_list, bool verbose);

template <class TreeType>
void run(TreeType tree, const string_t name, const cmdline::options_t& options, string_list_t& string_list);

template <class TreeType>
void simulate(TreeType tree, const cmdline::simulation_options_t options, const string_list_t& string_list);


int main(int argc, char* argv[]) {
	string_list_t list;
	cmdline::options_t options;

	if (argc == 1) {
		cmdline::usage();
		return 1;
	}

	if (!parse(argc, argv, options)) {
		return 1;
	}

	if (!load_input_file(options.filename, list, options.verbose)) {
		printf("can't load '%s'\n", options.filename.c_str());
		return 1;
	}

#define RUN_BODY \
	const string_t name = cmdline::structure_name(options); \
	Tree tree; \
	run<Tree>(tree, name, options, list); \

#define RUN(__type__) { \
	typedef __type__ Tree; \
	RUN_BODY\
}

#define FOREST(__hash__, __bits__) { \
	typedef HashedTree<__hash__> HashedTreeType; \
	typedef OneLevelTrie<HashedTreeType, __bits__> Tree; \
	const string_t name = cmdline::structure_name(options); \
	Tree tree; \
	run<Tree>(tree, name, options, list); \
}


	if (options.structure == cmdline::BST) {
		RUN(BST);
	} else
	if (options.structure == cmdline::STL_Map) {
		RUN(StlMapAdapter);
	} else
	if (options.structure == cmdline::STL_Unordered_Map) {
		RUN(StlUnorderedMapAdapter);
	} else
	if (options.structure == cmdline::Trie) {
		switch (options.hash) {
			case cmdline::FNV: {
				//typedef Trie<Fnv32, TrieLevels5<14,5,3,3,3> > Tree;
				//typedef Trie<Fnv32, TrieLevels5<16,4,4,4,4> > Tree;
				//typedef Trie<Fnv32, TrieLevels5<13,6,3,3,3> > Tree;
				typedef Trie<Fnv32, TrieLevels5<12,7,3,3,3> > Tree;
				RUN_BODY;
				}
				break;

			case cmdline::Murmur:
				break;

			case cmdline::None:
				break;
		}
	} else
	if (options.structure == cmdline::HashedTree) {
		switch (options.hash) {
			case cmdline::FNV:
				RUN(HashedTree<Fnv32>)
				break;

			case cmdline::Murmur:
				RUN(HashedTree<Murmur32>)
				break;

			case cmdline::None:
				break;
		}
	} else 
	if (options.structure == cmdline::HashedTreeEarlyRotate) {
		switch (options.hash) {
			case cmdline::FNV:
				RUN(HashedTreeEarlyRotate<Fnv32>)
				break;

			case cmdline::Murmur:
				RUN(HashedTreeEarlyRotate<Murmur32>)
				break;

			case cmdline::None:
				break;
		}
	} else 
	if (options.structure == cmdline::ForestOfHashedTrees) {
		switch (options.hash) {
			case cmdline::FNV:
				switch (options.forest_bits) {
					case 3:
						FOREST(Fnv32, 3)
						break;
					case 4:
						FOREST(Fnv32, 4)
						break;
					case 6:
						FOREST(Fnv32, 6)
						break;
					case 8:
						FOREST(Fnv32, 8)
						break;
					case 10:
						FOREST(Fnv32, 10)
						break;
					case 12:
						FOREST(Fnv32, 12)
						break;
					case 14:
						FOREST(Fnv32, 14)
						break;
					case 16:
						FOREST(Fnv32, 16)
						break;
					case 18:
						FOREST(Fnv32, 18)
						break;
				}
				break;

			case cmdline::Murmur:
				switch (options.forest_bits) {
					case 3:
						FOREST(Murmur32, 3)
						break;
					case 4:
						FOREST(Murmur32, 4)
						break;
					case 6:
						FOREST(Murmur32, 6)
						break;
					case 8:
						FOREST(Murmur32, 8)
						break;
					case 10:
						FOREST(Murmur32, 10)
						break;
					case 12:
						FOREST(Murmur32, 12)
						break;
					case 14:
						FOREST(Murmur32, 14)
						break;
					case 16:
						FOREST(Murmur32, 16)
						break;
					case 18:
						FOREST(Murmur32, 18)
						break;
				}
				break;
				break;

			case cmdline::None:
				break;
		}
	} else {
		puts("bug in cmdline.cpp or main.cpp");
		return 1;
	}

	return 0;
}


bool load_input_file(const string_t filename, string_list_t& string_list, const bool verbose) {
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.is_open()) {
		return false; 
	}

	size_t n = 0;
	printf("loading '%s'...", filename.c_str());
	while (std::getline(file, line)) {
		string_list.push_back(line);
		if (verbose && (n % 1000 == 0)) {
			printf("... %u lines\n", n);
		}

		n += 1;
	}
	puts("done");

	file.close();

	return true;
}


template <class TreeType>
void run(TreeType tree, const string_t name, const cmdline::options_t& options, string_list_t& string_list) {
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
void simulate(TreeType tree, const cmdline::simulation_options_t options, const string_list_t& string_list) {
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

