========================================================================
           Random binary trees - performance results
========================================================================

Introduction
------------------------------------------------------------------------

Following implementations are available (I know, names aren't perfect):

BST
	binarny search tree

	``-t`` option name: ``bst``

Hash (FNV32)
	BST where keys are hashed values using FNV algorithm

	``-t`` option name: ``fnv32``

Hash (FNV32) with early rotate
	see ``py/README.rst`` for details

	``-t`` option name: ``earlyrotate``

One level trie (FNV32)
	set of hashed trees, selected by k lowest bits of hash, in this case k=8

	``-t`` option name: ``fnv32-8``

STL map
	standard ``map`` (``libc++`` from gcc 4.8);

	``-t`` option name: ``map``

STL unordered map
	standard ``unordered_map`` (``libc++`` from gcc 4.8).

	``-t`` option name: ``unordered_map``

Compilation::

	$ g++ -std=c++11 -O2 -Wall main.cpp random.cpp cmdline.cpp -o your_favorite_name


Experiments (one thread)
------------------------------------------------------------------------

The same data as in python programs. Test program executes 1,000,000 steps,
in each step either insert or find function is called.

Test were run 5 times on my old laptop (Pentium M, 1.5GHz). Best times
are considered.

+-----------------+---------------+------------+
| insert/find [%] | *tree*        | time [ms]  |
+=================+===============+============+
|                 | BST           | 1735       |
|                 +---------------+------------+
|                 | fnv32         | 734        |
|                 +---------------+------------+
|     25%         | earlyrotate   | 723        |
|                 +---------------+------------+
|                 | fnv32-8       | 649        |
|                 +---------------+------------+
|                 | map           | 988        |
|                 +---------------+------------+
|                 | unordered_map | 520        |
+-----------------+---------------+------------+
|                 | BST           | 2109       |
|                 +---------------+------------+
|                 | fnv32         | 782        |
|                 +---------------+------------+
|     50%         | earlyrotate   | 733        |
|                 +---------------+------------+
|                 | fnv32-8       | 706        |
|                 +---------------+------------+
|                 | map           | 1037       |
|                 +---------------+------------+
|                 | unordered_map | 551        |
+-----------------+---------------+------------+
|                 | BST           | 2444       |
|                 +---------------+------------+
|                 | fnv32         | 784        |
|                 +---------------+------------+
|     75%         | earlyrotate   | 750        |
|                 +---------------+------------+
|                 | fnv32-8       | 688        |
|                 +---------------+------------+
|                 | map           | 1045       |
|                 +---------------+------------+
|                 | unordered_map | 538        |
+-----------------+---------------+------------+
|                 | BST           | 2520       |
|                 +---------------+------------+
|                 | fnv32         | 776        |
|                 +---------------+------------+
|     90%         | earlyrotate   | 748        |
|                 +---------------+------------+
|                 | fnv32-8       | 685        |
|                 +---------------+------------+
|                 | map           | 1021       |
|                 +---------------+------------+
|                 | unordered_map | 522        |
+-----------------+---------------+------------+
