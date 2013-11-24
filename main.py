import sys
from cmdline import get_options
from Tree import Tree
from tree_stats import *

def main(argv):
	options = get_options(argv)

	data = load_data(options)

	tree = Tree()
	get_key = options.key_function

	print "inserting data using function %s..." % options.key
	for i, string in enumerate(data):
		tree.insert(get_key(string), string)

	print "getting stats..."
	stats = get_stats(tree)

	print "statistics"
	print_stats(stats)

	if options.histogram:
		print_histogram(stats, 50, '#')


def load_data(options):
	print "loading data"
	with open(options.file) as f:
		data = f.readlines()

	if options.limit:
		print "... trimming to %d entries" % options.limit
		data = data[:options.limit]

	if options.sort:
		print "... sorting"
		data.sort()
	
	return data

if __name__ == '__main__':
	main(sys.argv)

