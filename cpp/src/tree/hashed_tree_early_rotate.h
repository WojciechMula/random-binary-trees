#ifndef hashed_tree_early_rotate_h_included__
#define hashed_tree_early_rotate_h_included__

#include "node.h"
#include "hashed_tree.h"

void dump(Node* root, int depth = 0) {
	if (!root)
		return;

	int i = depth;
	while (i--) putchar(' ');
	printf("%s\n", root->string.c_str());

	dump(root->left, depth + 1);
	dump(root->right, depth + 1);
}

template <class Hash>
class HashedTreeEarlyRotate: public HashedTree<Hash> {
	public:
		HashedTreeEarlyRotate() : HashedTree<Hash>() {}

		bool insert(const string_t string) {
			const hash_t hash = Hash::get(string);
			if (!this->root) {
				this->root = new Node(hash, string);
				return true;
			}

			Node* parent = 0;
			Node* prev = 0;
			Node* node = this->root;
			Node* next;
			while (true) {
				if (hash < node->hash) {
					if (node->left)
						next = node->left;
					else {
						Node* new_node = new Node(hash, string);
						if (!early_rotate(new_node, node, prev, parent))
							node->left = new_node;

						return true;
					}
				} else
				if (hash > node->hash) {
					if (node->right)
						next = node->right;
					else {
						Node* new_node = new Node(hash, string);
						if (!early_rotate(new_node, node, prev, parent))
							node->right = new_node;

						return true;
					}
				} else {
					// collisions are not handled yet
					return false;
				}

				parent = prev;
				prev = node;
				node = next;
				next = 0;
			}
		}

	protected:
		
		bool early_rotate(Node* new_node, Node* node, Node* prev, Node* parent) {
			if (parent == 0) {
				return false;
			}

			if (node->children_count() != 0 || prev->children_count() != 1) {
				return false;
			}

			if (new_node->hash < node->hash) {
				if (prev->left == node) {
					/*
					 *      prev
					 *       /
					 *     node
					 *     /
					 *  new_node
					 */
					
					node->left  = new_node;
					node->right = prev;

					parent->replace_child(prev, node);
					prev->make_leaf();
				} else {
					/*
					 *  prev
					 *     \
					 *     node
					 *     /
					 *  new_node
					 */
					new_node->left  = prev;
					new_node->right = node;

					parent->replace_child(prev, new_node);
					prev->make_leaf();
				}
			} else {
				if (prev->left == node) {
					/*
					 *   prev
					 *    /
					 *  node
					 *    \
					 *    new_node
					 */
					new_node->left  = node;
					new_node->right = prev;

					parent->replace_child(prev, new_node);
					prev->make_leaf();
				} else {
					/*
					 *  prev
					 *     \
					 *     node
					 *       \
					 *       new_node
					 */
					node->left  = prev;
					node->right = new_node;

					parent->replace_child(prev, node);
					prev->make_leaf();
				}
			}

			return true;
		}

};

#endif
