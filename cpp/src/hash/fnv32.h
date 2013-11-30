#ifndef fnv32_h_included__
#define fnv32_h_included__

#include "../types.h"

const uint32_t offset_basis = 2166136261u;
const uint32_t prime = 16777619u;

class Fnv32 {
	public:
	static hash_t get(const string_t str) {
		uint32_t hash = offset_basis;
		uint8_t *byte = (uint8_t*)str.c_str();

		while (*byte) {
			hash  = hash ^ *byte;
			hash *= prime;

			byte++;
		}

		return hash;
	}
};

#endif
