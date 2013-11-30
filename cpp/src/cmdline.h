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

	cmdline_options_t() :
		filename(""),
		simulation_options(),
		verify(false)
	{
		trees.insert("bst");
		trees.insert("fnv32");
		trees.insert("earlyrotate");
		trees.insert("fnv32-8");
		trees.insert("map");
		trees.insert("unordered_map");
	}
};

void usage();
bool parse(int argc, char* argv[], cmdline_options_t& options);

} // namespace

#endif
