#ifndef trie_h_included__
#define trie_h_included__

#include "../types.h"

/*

Trie with non-constant alphabet.

Path in trie is a 32-bit hash value, which is split to non-equal
size bitfields and each field is used at different tree level.
Bitfield size is defined in get_bits method.

The downside of this representation is big internal memory fragmentation,
about 80-90%.

*/
template <class Hash>
class Trie {
	public:
		void** root;
		size_t allocated;
		size_t nonzero;

	public:
		Trie<Hash>(): allocated(0), nonzero(0) {
			root = (void**)get_array(0);
		}

		~Trie<Hash>() {
#ifdef DEBUG
			printf("allocated  : %d\n", allocated);
			printf("nonzero    : %d\n", nonzero);
			printf("total size : %d B\n", allocated * sizeof(void*));
#endif
		}

		bool insert(string_t string) {
			hash_t hash = Hash::get(string);
			void** array = root;
			for (int level = 0; level < get_max_level(); level++) {
				const int bits    = get_bits(level);
				const hash_t part = hash & get_mask(level);
				hash >>= bits;

				void* ptr = array[part];

				if (ptr == 0) {
					ptr = get_array(level + 1);

					array[part] = ptr;
					nonzero += 1;
				}

				array = (void**)ptr;
			}

			return true;
		}

		bool find(string_t string) {
			hash_t hash = Hash::get(string);
			void** array = root;
			for (int level = 0; level <= get_max_level(); level++) {
				const int bits    = get_bits(level);
				const hash_t part = hash & get_mask(level);
				hash >>= bits;

				void** ptr = &array[part];

				if (level == get_max_level()) {
					return (ptr != 0);
				}

				array = ptr;
			}

			return true;
		}

	private:
		int get_bits(const int level) const {
			switch (level) {
				case 0:
					return 14;

				case 1:
					return 5;

				case 2:
					return 4;

				case 3:
				case 4:
				case 5:
					return 3;

				default:
					return 0;
			}
		}

		int get_max_level() const {
			return 5;
		}

		int get_count(int level) const {
			const int bits = get_bits(level);

			return 1 << bits;
		}

		int get_mask(int level) const {
			return get_count(level) - 1;
		}

		void* get_array(int level) {
			const int count = get_count(level);

			allocated += count;

			return calloc(count, sizeof(void*));
		}
};

#endif
