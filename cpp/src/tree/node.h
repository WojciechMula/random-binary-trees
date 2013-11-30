#ifndef node_h_included__
#define node_h_included__

#include "../types.h"

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

#endif
