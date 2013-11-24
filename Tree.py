from Node import Node

class Tree:
	def __init__(self):
		self.root = None


	def insert(self, key, value):
		if self.root is None:
			self.root = Node(key, value)
			return self.root

		node = self.root
		while True:
			if key < node.get_key():
				if node.left:
					node = node.left
				else:
					leaf = Node(key, value)
					node.left = leaf
					return leaf
			elif key > node.get_key():
				if node.right:
					node = node.right
				else:
					leaf = Node(key, value)
					node.right = leaf
					return leaf
			else:
				if not node.has_value(value):
					node.add_value(value)

				return node

	def find(self, key):
		node = self.root
		while node:
			if key == node.get_key():
				return node

			if key < node.get_key():
				node = node.left
			else:
				node = node.right


	def iter(self):
		queue = [(self.root, 0)]

		while queue:
			node, depth = queue.pop()
			if node is None:
				continue

			yield node, depth

			if node.left:
				queue.append((node.left, depth + 1))
			if node.right:
				queue.append((node.right, depth + 1))

if __name__ == '__main__':
	data = [
		(1, 'cat'),
		(8, 'dog'),
		(3, 'tree'),
		(10, 'sky'),
		(7, 'river'),
		(2, 'butterfly'),
		(5, 'bird'),
		(4, 'rock'),
		(6, 'mountain'),
		(10, 'cloud'),
	]

	t = Tree()
	for key, value in data:
		t.insert(key, value)

	for key, value in data:
		node = t.find(key)
		assert node is not None
		assert node.has_value(value)

	assert t.find(99) is None
