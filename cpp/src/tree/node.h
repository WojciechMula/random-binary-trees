#ifndef node_h_included__
#define node_h_included__

#include "../types.h"

class NotAChildError {
};

class ConstraintViolationError {
};

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

		int children_count() {
			const int count = ((int)(left != 0)) + ((int)(right != 0));

			return count;
		}

		void make_leaf() {
			left = right = 0;
		}

		void replace_child(Node* child, Node* new_child) {
			if (child == left) {
				left = new_child;
			} else
			if (child == right) {
				right = new_child;
			} else {
				throw NotAChildError();
			}
		}

		void check() {
			if (left && left->hash >= hash)
				throw ConstraintViolationError();

			if (right && right->hash <= hash)
				throw ConstraintViolationError();

		}
};

#endif
