#ifndef trie_levels_h_included__
#define trie_levels_h_included__

template <int n0, int n1, int n2, int n3, int n4>
class TrieLevels5 {
	public:
		static int get_bits(const int level) {
			switch (level) {
				case 0: return n0;
				case 1: return n1;
				case 2: return n2;
				case 3: return n3;
				case 4: return n4;

				default: return 0;
			}
		}

		static int get_max_level() {
			return 5;
		}

		static int get_count(int level) {
			const int bits = get_bits(level);

			return 1 << bits;
		}

		static int get_mask(int level) {
			return get_count(level) - 1;
		}
};

#endif

