#ifndef one_level_trie_h_included__
#define one_level_trie_h_included__

#include <vector>
#include "node.h"
#include "hashed_tree.h"

template <class HashedTreeType, int k>
class OneLevelTrie {
	public:
		std::vector<HashedTreeType> trees;

	public:
		OneLevelTrie() : trees(1 << k) {}

		bool insert(const string_t string) {
			const hash_t hash = HashedTreeType::get(string);

			return get(hash).insert_hashed(hash, string);
		}

		Node* find(const string_t string) {
			const hash_t hash = HashedTreeType::get(string);

			return get(hash).find_hashed(hash, string);
		}

	protected:
		HashedTreeType& get(const hash_t hash) {
			uint32_t mask = (1 << k) - 1;

			return trees[hash & mask];
		}
};

#endif
