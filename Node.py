class Node:

	__slots__ = ['key', 'values', 'left', 'right']
	
	def __init__(self, key, value):
		self.key = key
		self.values = [value]
		self.left = None
		self.right = None


	def children_count(self):
		return int(self.left is not None) + int(self.right is not None)


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


	def replace_child(self, child, new_node):
		if self.left is child:
			self.left = new_node
		elif self.right is child:
			self.right = new_node
		else:
			raise ValueError('replace_child: not a child')


	def validate(self):
		if self.left:
			assert self.left.key < self.key, 'left child has key greater or equal'

		if self.right:
			assert self.right.key > self.key, 'left child has key less or equal'
