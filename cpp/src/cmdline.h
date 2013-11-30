#ifndef cmdline_h_included__
#define cmdline_h_included__

#include "types.h"
#include <set>

namespace cmdline {

struct simulation_options_t {
	int steps;
	int seed;
	int insert_probability;

	simulation_options_t() :
		steps(1000000),
		seed(20131130),
		insert_probability(50)
	{}
};

struct cmdline_options_t {
	string_t filename;
	simulation_options_t simulation_options;
	bool verify;
	std::set<string_t> trees;
	std::set<string_t> all_trees;

	cmdline_options_t() :
		filename(""),
		simulation_options(),
		verify(false)
	{
		all_trees.insert("bst");
		all_trees.insert("fnv32");
		all_trees.insert("earlyrotate");
		all_trees.insert("fnv32-8");
		all_trees.insert("map");
		all_trees.insert("unordered_map");
	}

	bool use_tree(const string_t name) {
		if (all_trees.count(name)) {
			trees.insert(name);

			return true;
		} else {
			return false;
		}
	}

	void use_all_trees() {
		trees = all_trees;
	}
};

void usage();
bool parse(int argc, char* argv[], cmdline_options_t& options);

} // namespace

#endif
