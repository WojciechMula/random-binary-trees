/*
	Modification of BST - each node store k distinct values,
	left and right children have values less/greater then
	least/greatest in the node.
*/
#ifndef tree_h_included__
#define tree_h_included__

#include "../types.h"
#include <algorithm>

template <int k>
class MultivalueNode {
	public:
		int count = 0;
		hash_t hashes[k];

		MultivalueNode<k>* left = nullptr;
		MultivalueNode<k>* right = nullptr;

	public:
		MultivalueNode() {
			for (int i=0; i < k; i++)
				hashes[i] = 0;
		}

		// this function could be coded with few SSE instructions
		bool has(const hash_t hash) const {
			for (int i=0; i < count; i++) {
				if (hash == hashes[i])
					return true;
			}

			return false;
		}

		bool add(const hash_t hash) {
			if (count < k) {
				hashes[count++] = hash;
				std::sort(hashes, hashes + count);

				return true;
			} else
				return false;
		}

		hash_t min() const {
			return hashes[0];
		}

		hash_t max() const {
			if (count > 0)
				return hashes[count - 1];
			else
				return min();
		}
};

template <class Hash, int k>
class MultivalueTree {
	public:
		typedef MultivalueNode<k> Node;

		Node* root = nullptr;

	public:
		bool insert(string_t string) {
			hash_t hash = Hash::get(string);
			if (!root) {
				root = new Node();
				root->add(hash);
				return true;
			}

			Node* node = root;
			while (true) {
				if (node->add(hash))
					return true;

				if (hash < node->min()) {
					if (node->left == nullptr)
						node->left = new Node();

					node = node->left;
				} else
				if (hash > node->max()) {
					if (node->right == nullptr)
						node->right = new Node();

					node = node->right;
				} else {
					if (node->left == nullptr) {
						std::vector<hash_t> tmp;

						tmp.push_back(hash);
						for (int i=0; i < k; i++)
							tmp.push_back(node->hashes[i]);

						std::sort(tmp.begin(), tmp.end());

						for (int i=0; i < k; i++) {
							node->hashes[i] = tmp[i+1];
						}

						node->left = new Node();
						assert(node->left->add(tmp[0]));

						return true;
					} else
					if (node->right == nullptr) {
						std::vector<hash_t> tmp;

						tmp.push_back(hash);
						for (int i=0; i < k; i++)
							tmp.push_back(node->hashes[i]);


						std::sort(tmp.begin(), tmp.end());

						for (int i=0; i < k; i++) {
							node->hashes[i] = tmp[i];
						}

						node->right = new Node();
						assert(node->right->add(tmp[k]));

						return true;
					} else {
						std::vector<hash_t> tmp;

						tmp.push_back(hash);
						for (int i=0; i < k; i++)
							tmp.push_back(node->hashes[i]);


						std::sort(tmp.begin(), tmp.end());

						for (int i=0; i < k; i++) {
							node->hashes[i] = tmp[i];
						}

						hash = tmp[k];
						node = node->right;
					}
				}
			}
		}

		bool find(string_t string) {
			Node* node = root;
			const hash_t hash = Hash::get(string);

			while (node) {
				if (hash < node->min())
					node = node->left;
				else
				if (hash > node->max())
					node = node->right;
				else
					return node->has(hash);
			}

			return false;
		}

};

#endif
