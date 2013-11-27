# BST variant that does simple rotation in case when adding
# new node would produce a chain like this:
# 
#                  prev2
#                  /  \
#                prev1 ...
#                /
#              node
#              /
#          new node
# 
# Subtree rooted at prev is rotated (in constant time) producing:
# 
#                  prev2
#                  /  \
#                node ...
#                /  \
#          new node  prev

from Tree import Tree
from Node import Node

class TreeEarlyRotate(Tree):
	def insert(self, key, value):
		if self.root is None:
			self.root = Node(key, value)
			return self.root

		prev3 = None
		prev2 = None
		prev1 = None
		node  = self.root

		def rotate_when_less(new_leaf):
			if prev1 is None or prev2 is None:
				return

			if node.children_count() == 0 and prev1.children_count() == 1:
				assert new_leaf.key < node.key

				if node is prev1.left:
					prev2.replace_child(prev1, node)
					node.left  = new_leaf
					node.right = prev1
				else:
					prev2.replace_child(prev1, new_leaf)
					new_leaf.left  = prev1
					new_leaf.right = node

				prev1.make_leaf()

				new_leaf.validate()
				node.validate()
				prev1.validate()
				prev2.validate()

				return True


		def rotate_when_greater(new_leaf):
			if prev1 is None or prev2 is None:
				return

			if node.children_count() == 0 and prev1.children_count() == 1:
				assert new_leaf.key > node.key

				if node is prev1.right:
					prev2.replace_child(prev1, node)

					node.right = new_leaf
					node.left  = prev1
				else:
					prev2.replace_child(prev1, new_leaf)

					new_leaf.right = prev1
					new_leaf.left  = node

				prev1.make_leaf()

				new_leaf.validate()
				node.validate()
				prev1.validate()
				prev2.validate()

				return True


		def balance_subtree(new_leaf):
			if prev3 is None:
				return

			assert prev3 is not None
			assert prev2 is not None
			assert prev1 is not None
			assert prev3.is_parent(prev2)
			assert prev2.is_parent(prev1)
			assert prev1.is_parent(node)

			def is_skew(node, child):
				other = node.other_child(child)
				return other is None or other.is_leaf()

			if not is_skew(prev2, prev1):
				return

			if not is_skew(prev1, node):
				return

			if not node.children_count() < 2:
				return
			
			all_nodes = [
				new_leaf,
				node,
				node.left,
				node.right,
				prev1,
				prev1.other_child(node),
				prev2,
				prev2.other_child(prev1)
			]

			subtree_nodes = [n.make_leaf() for n in all_nodes if n is not None]
			subtree_nodes.sort(key=lambda node: node.key)

			def aux(a, b):
				if a > b:
					return

				c = (a + b)/2

				node = subtree_nodes[c]

				node.left  = aux(a, c - 1)
				node.right = aux(c + 1, b)

				return node

			new = aux(0, len(subtree_nodes) - 1)

			prev3.replace_child(prev2, new)

			#print "here"
			return True


		while True:
			if key < node.get_key():
				if node.left:
					next = node.left
				else:
					new_leaf = Node(key, value)
					if not rotate_when_less(new_leaf) and not balance_subtree(new_leaf):
						node.left = new_leaf

					return new_leaf
			elif key > node.get_key():
				if node.right:
					next = node.right
				else:
					new_leaf = Node(key, value)
					if not rotate_when_greater(new_leaf) and not balance_subtree(new_leaf):
						node.right = new_leaf

					return new_leaf
			else:
				if not node.has_value(value):
					node.add_value(value)

				return node


			prev3 = prev2
			prev2 = prev1
			prev1 = node
			node  = next
