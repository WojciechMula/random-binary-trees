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

from TreeCustomInsert import TreeCustomInsert

class TreeEarlyRotate(TreeCustomInsert):
	def custom_insert_left(self, new_leaf, node, prev1, prev2, prev3):
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


	def custom_insert_right(self, new_leaf, node, prev1, prev2, prev3):
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

