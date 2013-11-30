from pyavltree import AVLTree, Node as AVLNode

class AVLNodeAdapter(object):
	def __init__(self, avl_node):
		self.node = avl_node

	def get_values(self):
		return []


class AVLTreeAdapter(object):
	def __init__(self):
		self.avl = AVLTree()

	def insert(self, key, value):
		self.avl.insert(key)

	def find(self, key):
		node = self.avl.find(key)

		if node is not None:
			return AVLNodeAdapter(node)

	def iter(self):
		queue = [(self.avl.rootNode, 0)]

		while queue:
			node, depth = queue.pop()
			if node is None:
				continue

			yield AVLNodeAdapter(node), depth

			if node.leftChild:
				queue.append((node.leftChild, depth + 1))
			if node.rightChild:
				queue.append((node.rightChild, depth + 1))

