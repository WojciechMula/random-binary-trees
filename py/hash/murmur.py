# 32-bit Murmur hash function

c1 = 0xcc9e2d51
c2 = 0x1b873593
r1 = 15
r2 = 13
m  = 5
n  = 0xe6546b64

def mul(a, b):
	return (a * b) & 0xffffffff

def add(a, b):
	return (a + b) & 0xffffffff

def shr(a, n):
	return (a & 0xffffffff) >> n

def shl(a, n):
	return (a << n) & 0xffffffff

def get(string):
	hash = 0xdeadbeef

	rounded = 4*(len(string)/4)

	for i in xrange(0, rounded, 4):
		byte0 = ord(string[i + 0])
		byte1 = ord(string[i + 1])
		byte2 = ord(string[i + 2])
		byte3 = ord(string[i + 3])
		
		k = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0

		k = mul(k, c1)
		k = shl(k, r1) | shr(hash, 32 - r1)
		k = mul(k, c2)

		hash = hash ^ k
		hash = shl(hash, r2) | shr(hash, 32 - r2)
		hash = mul(hash, m)
		hash = add(hash, n)

	if len(string) % 4 > 0:
		t = len(string) % 4
		tail = string[-t:]

		def get_byte(i):
			try:
				return ord(tail[i])
			except IndexError:
				return 0

		k = (get_byte(3) << 24) | (get_byte(2) << 16) | (get_byte(1) << 8) | get_byte(0)

		k = mul(k, c1)
		k = shl(k, r1) | shr(hash, 32 - r1)
		k = mul(k, c2)

		hash = hash ^ k


	hash = hash ^ (len(string) & 0xffffffff)
	hash = hash ^ shr(hash, 16)
	hash = mul(hash, 0x85ebca6b)
	hash = hash ^ shr(hash, 13)
	hash = mul(hash, 0xc2b2ae35)
	hash = hash ^ shr(hash, 16)

	return hash
