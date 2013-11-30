#ifndef cmdline_h_included__
#define cmdline_h_included__

#include "types.h"

struct simulation_options_t {
	int steps;
	int seed;

	simulation_options_t() :
		steps(1000000),
		seed(20131130)
	{}
};

struct cmdline_options_t {
	string_t filename;
	simulation_options_t simulation_options;
	bool verify;

	cmdline_options_t() :
		filename(""),
		verify(false),
		simulation_options()
	{}
};

#endif
