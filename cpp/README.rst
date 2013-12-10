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

