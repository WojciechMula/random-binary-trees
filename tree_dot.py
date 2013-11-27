import avl
from avl.pyavltree import Node as AVLNode
from avl.adapters import AVLNodeAdapter


def export(tree, name, file):
	"save tree in a dot format"

	indexes = {}
	index   = 1
	for node, depth in tree.iter():
		indexes[id(node)] = index
		index += 1

	def writeln(s):
		file.write(s)
		file.write('\n')

	def write_edge(node_from, node_to):
		index_from = indexes[id(node_from)]
		index_to   = indexes[id(node_to)]

		writeln('\tn%d -> n%d' % (index_from, index_to))

	writeln('digraph %s {' % name)
	for node, depth in tree.iter():
		if node.left:
			write_edge(node, node.left)
		if node.right:
			write_edge(node, node.right)

	writeln('}')

