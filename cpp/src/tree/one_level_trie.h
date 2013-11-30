#ifndef one_level_trie_h_included__
#define one_level_trie_h_included__

#include <vector>
#include "node.h"
#include "hashed_tree.h"

template <class Hash, int k>
class OneLevelTrie {
	public:
		std::vector<HashedTree<Hash> > trees;

	public:
		OneLevelTrie() : trees(1 << k) {}

		bool insert(const string_t string) {
			const hash_t hash = Hash::get(string);

			return get(hash).insert_hashed(hash, string);
		}

		Node* find(const string_t string) {
			const hash_t hash = Hash::get(string);

			return get(hash).find_hashed(hash, string);
		}

	protected:
		HashedTree<Hash>& get(const hash_t hash) {
			uint32_t mask = (1 << k) - 1;

			return trees[hash & mask];
		}
};

#endif
