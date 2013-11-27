from Tree import Tree
from TreeEarlyRotate import TreeEarlyRotate
from TreeEarlyRotate2 import TreeEarlyRotate2

import avl
from avl.adapters import AVLTreeAdapter

trees = {
	'bst': Tree,
	'avl': AVLTreeAdapter,
	'earlyrotate': TreeEarlyRotate,
	'earlyrotate2': TreeEarlyRotate2,
}
