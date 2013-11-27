# BST variant that does simple rotation in case when adding
# new node would produce a chain like this (leafs are optional):
# 
#                     prev3 [subtree parent]
#                     /
#                   prev2
#                   /  \
#                prev1 leaf1
#                /   \
#              node leaf2
#             /   \
#        new node leaf3
# 
# Subtree rooted at prev2 is balaced.

from TreeEarlyRotate import TreeEarlyRotate

class TreeEarlyRotate2(TreeEarlyRotate):

	def custom_insert_left(self, *args):
		if not super(TreeEarlyRotate, self).custom_insert_left(*args):
			return self.balance_subtree(*args)


	def custom_insert_right(self, *args):
		if not super(TreeEarlyRotate, self).custom_insert_right(*args):
			return self.balance_subtree(*args)


	def balance_subtree(self, new_leaf, node, prev1, prev2, prev3):
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

		if node.children_count() == 2:
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

		return True

