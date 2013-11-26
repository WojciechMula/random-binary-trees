# BST variant that does simple rotation in case when adding
# new node would produce a chain like this:
# 
#                 parent
#                  /  \
#                prev ...
#                /
#              node
#              /
#          new node
# 
# Subtree rooted at prev is rotated (in constant time) producing:
# 
#                 parent
#                  /  \
#                node ...
#                /  \\
#          new node  prev

from Tree import Tree
from Node import Node

class TreeEarlyRotate(Tree):
	def insert(self, key, value):
		if self.root is None:
			self.root = Node(key, value)
			return self.root

		node = self.root

		parent = None
		prev = None

		def rotate_when_less(leaf):
			if prev is None or parent is None:
				return

			if node.children_count() == 0 and prev.children_count() == 1:
				assert leaf.key < node.key

				if node == prev.left:
					parent.replace_child(prev, node)
					node.left  = leaf
					node.right = prev
				else:
					parent.replace_child(prev, leaf)
					leaf.left  = prev
					leaf.right = node

				prev.left = prev.right = None

				leaf.validate()
				prev.validate()
				node.validate()
				parent.validate()

				return True

		def rotate_when_greater(leaf):
			if prev is None or parent is None:
				return

			if node.children_count() == 0 and prev.children_count() == 1:
				assert leaf.key > node.key

				if node == prev.right:
					parent.replace_child(prev, node)

					node.right = leaf
					node.left  = prev
				else:
					parent.replace_child(prev, leaf)

					leaf.right = prev
					leaf.left  = node

				prev.left = prev.right = None
				leaf.validate()
				prev.validate()
				node.validate()
				parent.validate()

				return True


		while True:
			if key < node.get_key():
				if node.left:
					next = node.left
				else:
					leaf = Node(key, value)
					if not rotate_when_less(leaf):
						node.left = leaf

					return leaf
			elif key > node.get_key():
				if node.right:
					next = node.right
				else:
					leaf = Node(key, value)
					if not rotate_when_greater(leaf):
						node.right = leaf

					return leaf
			else:
				if not node.has_value(value):
					node.add_value(value)

				return node


			parent = prev
			prev   = node
			node   = next
