from math import log

def get_stats(tree):
	nodes  = 0
	values = 0
	collisions = 0
	depths = {}
	depth_sum = 0
	max_depth = 0
	avg_depth = None

	for node, depth in tree.iter():
		nodes  += 1
		depth_sum += depth
		max_depth = max(depth, max_depth)
		depths[depth] = depths.get(depth, 0) + 1

		k = len(node.get_values())
		values += k
		if k > 1:
			collisions += k

	if nodes > 0:
		avg_depth = depth_sum/float(nodes)

	return {
		'nodes'			: nodes,		# number of nodes
		'depths'		: depths,		# node's histogram
		'avg_depth'		: avg_depth,	# averge depth
		'max_depth'		: max_depth,	# max depth
		'values'		: values,		# number of values
		'collisions'	: collisions,	# number of distinct values with same key
	}


def print_stats(stats):

	n = stats['nodes']
	d = {
		'AVL_max_height' : 1.44*log(n + 2, 2.0) - 0.328,
		'RB_max_height'  : 2.00*log(n + 1, 2.0),
	}

	d.update(stats)

	print """
   nodes count: %(nodes)d
  values count: %(values)d
    collisions: %(collisions)d
     avg depth: %(avg_depth)0.2f
     max depth: %(max_depth)d
AVL max height: %(AVL_max_height)0.2f
R-b max height: %(RB_max_height)0.2f
""" % d


def print_histogram(stats, width, barchar='='):
	histogram = stats['depths']

	max_count = max(histogram.values())
	max_depth = max(histogram.keys())

	assert max_count > 0

	print 'depth histogram'
	print '-' * width
	print 'depth  count'
	for depth in xrange(0, max_depth + 1):
		count = histogram.get(depth, 0)
		perc  = count/float(max_count)

		print '%4d [%6d]: %s' % (depth, count, barchar*int(width*perc))
