class Node:

	__slots__ = ['key', 'values', 'left', 'right']
	
	def __init__(self, key, value):
		self.key = key
		self.values = [value]
		self.left = None
		self.right = None


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

