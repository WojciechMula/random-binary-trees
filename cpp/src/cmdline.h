#ifndef cmdline_h_included__
#define cmdline_h_included__

#include "types.h"

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

typedef enum {
	BST,					//< BST tree
	HashedTree,				//< BST tree with hashed keys
	HashedTreeEarlyRotate,	//< BST tree with hashed keys with "early rotate" optimization
	ForestOfHashedTrees,	//< Forest of "hashed trees"
	STL_Map,				//< std::map, usually red-black tree
	STL_Unordered_Map		//< std::unordered_map
} structure_kind_t;

typedef enum {
	None,
	FNV,
	Murmur
} hash_kind_t;


struct options_t {
	string_t filename;
	simulation_options_t simulation_options;
	bool verify;
	bool verbose;

	structure_kind_t structure;
	hash_kind_t		 hash;
	int				 forest_bits;

	options_t() :
		filename(""),
		simulation_options(),
		verify(false),
		verbose(false),
		structure(BST),
		hash(None),
		forest_bits(0)
	{
	}
};

void usage();
bool parse(int argc, char* argv[], options_t& options);
string_t structure_name(const options_t& options);

} // namespace

#endif
