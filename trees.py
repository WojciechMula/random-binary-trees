from Tree import Tree
from TreeEarlyRotate import TreeEarlyRotate

import avl
from avl.adapters import AVLTreeAdapter

trees = {
	'bst': Tree,
	'avl': AVLTreeAdapter,
	'earlyrotate': TreeEarlyRotate,
}
