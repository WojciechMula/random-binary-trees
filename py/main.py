import sys
from cmdline import get_options
from tree_stats import *
import balanced_tree

def main(argv):
	options = get_options(argv)

	data = load_data(options)

	print "*** tree: %s" % options.tree_name
	tree    = options.tree_class()
	get_key = options.key_function

	if options.perfect:
		print "ordering data to build balanced tree"
		data = balanced_tree.prepare_data(data, get_key)

	print "inserting data using function %s..." % options.key
	for i, string in enumerate(data):
		tree.insert(get_key(string), string)

	if options.validate:
		print 'validating...'
		#from dot import dot_export
		#with file('z.dot', 'w') as f:
		#	dot_export(tree, f)
		for string in data:
			assert tree.find(get_key(string)) is not None

	if options.dot_file:
		print "saving DOT file '%s'..." % options.dot_file
		with open(options.dot_file, 'wt') as f:
			from tree_dot import export
			export(tree, options.tree_name, f)

	print "getting stats..."
	stats = get_stats(tree)

	print "statistics"
	print_stats(stats)

	if options.histogram:
		print_histogram(stats, 65, '#')

	if options.histogram_file:
		with open(options.histogram_file, 'wt') as f:
			dump_histogram(stats, f)


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

