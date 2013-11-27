class Node:

	__slots__ = ['key', 'values', 'left', 'right']
	
	def __init__(self, key, value):
		self.key = key
		self.values = [value]
		self.left = None
		self.right = None


	def children_count(self):
		return int(self.left is not None) + int(self.right is not None)


	def is_leaf(self):
		return self.left is None and self.right is None


	def make_leaf(self):
		self.left = self.right = None

		return self


	def get_key(self):
		return self.key


	def get_value(self):
		return self.values[0]


	def get_values(self):
		return self.values


	def add_value(self, value):
		self.values.append(value)


	def has_value(self, value):
		return value in self.values
	

	def is_parent(self, child):
		return self.left is child or self.right is child


	def replace_child(self, child, new_node):
		if self.left is child:
			self.left = new_node
		elif self.right is child:
			self.right = new_node
		else:
			raise ValueError('replace_child: not a child')


	def other_child(self, child):
		if self.left is child:
			return self.right
		elif self.right is child:
			return self.left
		else:
			raise ValueError('other_child: not a child')


	def validate(self):
		if self.left:
			assert self.left.key < self.key, 'left child has key greater or equal'

		if self.right:
			assert self.right.key > self.key, 'right child has key less or equal'
