from Tree import Tree
from Node import Node

class TreeCustomInsert(Tree):

	def custom_insert_left(self, new_node, node, prev1, prev2, prev3):
		"returns True when new_node has been inserted to tree"
		pass

	def custom_insert_right(self, new_node, node, prev1, prev2, prev3):
		"returns True when new_node has been inserted to tree"
		pass

	def insert(self, key, value):
		if self.root is None:
			self.root = Node(key, value)
			return self.root

		prev3 = None
		prev2 = None
		prev1 = None
		node  = self.root

		while True:
			if key < node.get_key():
				if node.left:
					next = node.left
				else:
					new_leaf = Node(key, value)
					if not self.custom_insert_left(new_leaf, node, prev1, prev2, prev3):
						node.left = new_leaf

					return new_leaf
			elif key > node.get_key():
				if node.right:
					next = node.right
				else:
					new_leaf = Node(key, value)
					if not self.custom_insert_right(new_leaf, node, prev1, prev2, prev3):
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

