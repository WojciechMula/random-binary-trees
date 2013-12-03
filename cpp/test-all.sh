#!/bin/bash

if [[ ! -e "$1" ]]
then
	echo "'$1' not found"
	exit 1
fi

BIN=obj/test

ALL='bst earlyrotate fnv32 forest-earlyrotate-10 forest-earlyrotate-12 forest-earlyrotate-14 forest-earlyrotate-16 forest-earlyrotate-18 forest-earlyrotate-3 forest-earlyrotate-4 forest-earlyrotate-6 forest-earlyrotate-8 forest-hashed-10 forest-hashed-12 forest-hashed-14 forest-hashed-16 forest-hashed-18 forest-hashed-3 forest-hashed-4 forest-hashed-6 forest-hashed-8 map unordered_map'

OUTPUT=output.txt

rm -f $OUTPUT

for tree in $ALL
do
	$BIN -f "$1" --sim-steps 1000000 --sim-insert-prob 50 -t $tree | tee -a $OUTPUT
done
