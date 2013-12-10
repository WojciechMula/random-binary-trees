#ifndef murmur32_h_included__
#define murmur32_h_included__

#include "../types.h"

class Murmur32 {
	public:
	static hash_t get(const string_t str, const uint32_t seed = 0xdeadbeef) {
		uint32_t hash = seed;
		const size_t len = str.length();

		const uint32_t c1 = 0xcc9e2d51;
		const uint32_t c2 = 0x1b873593;
		const uint32_t r1 = 15;
		const uint32_t r2 = 13;
		const uint32_t m  = 5;
		const uint32_t n  = 0xe6546b64;

		const uint32_t rounded = 4*(len/4);
		for (size_t i=0; i < rounded; i += 4) {
			uint32_t k = ((uint32_t)(uint8_t)str[i + 0] <<  0) |
			             ((uint32_t)(uint8_t)str[i + 1] <<  8) |
			             ((uint32_t)(uint8_t)str[i + 2] << 16) |
			             ((uint32_t)(uint8_t)str[i + 3] << 24);

			k *= c1;
			k  = (k << r1) | (hash >> (32 - r1));
			k *= c2;

			hash = hash ^ k;
			hash = (hash << r2) | (hash >> (32 - r2));
			hash = hash * m + n;
		}

		const size_t tail = (len % 4);
		if (tail > 0) {
			uint32_t k;
			switch (tail) {
				case 1:
					k = (uint32_t)(uint8_t)str[len - 1];
					break;

				case 2:
					k = (((uint32_t)(uint8_t)str[len - 1]) <<  0) |
					    (((uint32_t)(uint8_t)str[len - 2]) <<  8);
					break;

				case 3:
					k = (((uint32_t)(uint8_t)str[len - 1]) <<  0) |
					    (((uint32_t)(uint8_t)str[len - 2]) <<  8) |
					    (((uint32_t)(uint8_t)str[len - 3]) << 16);
					break;

				default:
					abort();
			} 

			k *= c1;
			k  = (k << r1) | (hash >> (32 - r1));
			k *= c2;

			hash = hash ^ k;
		}

		hash = hash ^ len;
		hash = hash ^ (hash >> 16);
		hash = hash * 0x85ebca6b;
		hash = hash ^ (hash >> 13);
		hash = hash * 0xc2b2ae35;
		hash = hash ^ (hash >> 16);

		return hash;
	}

};

#endif
