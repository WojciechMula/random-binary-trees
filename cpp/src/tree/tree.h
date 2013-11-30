#ifndef tree_h_included__
#define tree_h_included__

#include "types.h"

class Node {
	public:
		hash_t hash;
		string_t  string;

		Node* left;
		Node* right;

	public:
		Node(hash_t hash, string_t string) :
			hash(hash),
			string(string),
			left(0),
			right(0)
		{}
};

template <class Hash>
class Tree {
	public:
		Node* root;

	public:
		Tree() : root(0) {}

		bool insert(string_t string) {
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

		Node* find(string_t string) {
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


class BasicTree {
	public:
		Node* root;

	public:
		Tree() : root(0) {}

		bool insert(string_t string) {
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

		Node* find(string_t string) {
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
