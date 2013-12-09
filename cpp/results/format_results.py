def main(filenames):
	for name in filenames:
		with open(name) as f:
			times = parse(f)
			format(times)


arguments = [
	('bst', 'BST'),
	('earlyrotate', 'Hash (FNV32) with early rotate'),
	('fnv32', 'Hash (FNV32)'),
	('forest-earlyrotate-10', 'One level trie - 10 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-12', 'One level trie - 12 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-14', 'One level trie - 14 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-16', 'One level trie - 16 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-18', 'One level trie - 18 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-3', 'One level trie - 3 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-4', 'One level trie - 4 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-6', 'One level trie - 6 bits [earlyrotate (FNV32)]'),
	('forest-earlyrotate-8', 'One level trie - 8 bits [earlyrotate (FNV32)]'),
	('forest-hashed-10', 'One level trie - 10 bits [hashed tree (FNV32)]'),
	('forest-hashed-12', 'One level trie - 12 bits [hashed tree (FNV32)]'),
	('forest-hashed-14', 'One level trie - 14 bits [hashed tree (FNV32)]'),
	('forest-hashed-16', 'One level trie - 16 bits [hashed tree (FNV32)]'),
	('forest-hashed-18', 'One level trie - 18 bits [hashed tree (FNV32)]'),
	('forest-hashed-3', 'One level trie - 3 bits [hashed tree (FNV32)]'),
	('forest-hashed-4', 'One level trie - 4 bits [hashed tree (FNV32)]'),
	('forest-hashed-6', 'One level trie - 6 bits [hashed tree (FNV32)]'),
	('forest-hashed-8', 'One level trie - 8 bits [hashed tree (FNV32)]'),
	('map', 'STL map'),
	('unordered_map', 'STL unordered map'),
]


def format(results):
	max_time = max(t for t in results.values())

	for name, title in arguments:
		value = results[title]
		perc  = float(value)/max_time

		print '\t* - %s' % name
		print '\t  - %d' % value
		print '\t  - %0.1f' % (100.0*perc)
		print '\t  - ``%s``' % ('=' * int(50.0 * perc))


def parse(file):
	lines = file.readlines()
	
	prefix = 'tree implementation '
	prefix_time = 'time:'
	result = {}

	for index, line in enumerate(lines):
		line = line.strip()
		if not line.startswith(prefix):
			continue

		name = line[len(prefix):-1]

		next = lines[index+3].split()
		assert next[0] == prefix_time

		result[name] = int(next[1])
	
	return result


if __name__ == '__main__':
	from sys import argv
	
	main(argv[1:])
