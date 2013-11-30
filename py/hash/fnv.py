# 32-bit Fowler-Noll-Vo hash function

offset_basis = 2166136261
prime = 16777619

def get(string):
	hash = offset_basis
	for char in string:
		byte = ord(char)

		hash  = hash ^ byte
		hash *= prime

		hash &= 0xffffffff

	return hash
