#ifndef hashed_tree_h_included__
#define hashed_tree_h_included__

#include "node.h"

template <class Hash>
class HashedTree {
	public:
		Node* root;

	public:
		HashedTree() : root(0) {}

		bool insert(const string_t string) {
			const hash_t hash = Hash::get(string);
			if (!root) {
				root = new Node(hash, string);
				return true;
			}

			Node* node = root;
			while (true) {
				if (hash < node->hash) {
					if (node->left)
						node = node->left;
					else {
						Node* new_leaf = new Node(hash, string);
						node->left = new_leaf;

						return true;
					}
				} else
				if (hash > node->hash) {
					if (node->right)
						node = node->right;
					else {
						Node* new_leaf = new Node(hash, string);
						node->right = new_leaf;

						return true;
					}
				} else {
					// collisions are not handled yet
					return false;
				}
			}
		}

		Node* find(const string_t string) {
			Node* node = root;
			const hash_t hash = Hash::get(string);

			while (node) {
				if (hash < node->hash) {
					node = node->left;
				} else
				if (hash > node->hash) {
					node = node->right;
				} else
					break;
			}
			
			return node;
		}
};

#endif
