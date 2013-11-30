#ifndef bst_h_included__
#define bst_h_included__

#include "node.h"

class BST {
	public:
		Node* root;

	public:
		BST() : root(0) {}

		bool insert(const string_t string) {
			const hash_t hash = 0;
			if (!root) {
				root = new Node(hash, string);
				return true;
			}

			Node* node = root;
			while (true) {
				if (string < node->string) {
					if (node->left)
						node = node->left;
					else {
						Node* new_leaf = new Node(hash, string);
						node->left = new_leaf;

						return true;
					}
				} else
				if (string > node->string) {
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
			while (node) {
				if (string < node->string) {
					node = node->left;
				} else
				if (string > node->string) {
					node = node->right;
				} else
					break;
			}
			
			return node;
		}
};

#endif
