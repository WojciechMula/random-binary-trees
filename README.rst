========================================================================
                       Random binary trees
========================================================================

Introduction
------------------------------------------------------------------------

Binary trees are sensitive to insertion order, in worst case [inserting
sorted values] tree becomes a list. AVL and RB trees overcome
this at cost of more complicated inserting/removing and additional storage.

However, instead of using AVL/RB it's possible to avoid degenerated
case. The idea is to use as key not value, but hashed value, which is
almost random.


Experiments
------------------------------------------------------------------------

Input is all paths form ``/usr``::

	$ find /usr > list
	$ wc -l list
	101374 list


Degenerated case --- inserting sorted data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

	$ python main.py -f ~/list -k value -l 100 -s
	loading data
	... trimming to 100 entries
	... sorting
	inserting data using function value...
	getting stats...
	statistics

	   nodes count: 100
	  values count: 100
	    collisions: 0
	     avg depth: 49.50
	     max depth: 99
	AVL max height: 9.28
	R-b max height: 13.32

When hash is used::

	$ python main.py -f ~/list -k hash -l 100 -s
	loading data
	... trimming to 100 entries
	... sorting
	inserting data using function hash...
	getting stats...
	statistics

	   nodes count: 100
	  values count: 100
	    collisions: 0
	     avg depth: 6.10
	     max depth: 11
	AVL max height: 9.28
	R-b max height: 13.32



Key is a value
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

	$ python main.py -f ~/list -k value
	loading data
	inserting data using function value...
	getting stats...
	statistics

	   nodes count: 101374
	  values count: 101374
	    collisions: 0
	     avg depth: 68.47
	     max depth: 187
	AVL max height: 23.62
	R-b max height: 33.26


Key is a hash value
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hash is value calculated by python interpreter.
There are **collisions**.

::

	$ python main.py -f ~/list -k hash
	loading data
	inserting data using function hash...
	getting stats...
	statistics

	   nodes count: 101373
	  values count: 101374
	    collisions: 2
	     avg depth: 20.13
	     max depth: 47
	AVL max height: 23.62
	R-b max height: 33.26


Key is a pseudorandom seeded by value
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Again **collisions**.

::

	$ python main.py -f ~/list -k random
	loading data
	inserting data using function random...
	getting stats...
	statistics

	   nodes count: 101371
	  values count: 101374
	    collisions: 6
	     avg depth: 21.06
	     max depth: 43
	AVL max height: 23.62
	R-b max height: 33.26

