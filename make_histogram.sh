#!/bin/bash

count=10000
file="$1"

if [[ ! -f "$1" ]]
then
	echo "Usage: $0 filename"
	exit 1
fi

function gather_data {
	for name in adler32 crc32 fnv hash md5 random value
	do
		python main.py -f "$file" -k $name -l $count --csv-histogram=${name}.csv
		true
	done

	python main.py -f "$file" -k value -l $count --avl --csv-histogram=avl.csv
}

function make_plots {
gnuplot << EOF
set terminal png medium size 800,600

set title  'Node depths histogram'
set ylabel 'frequency'
set xlabel 'depth'
set output 'histogram.png'

plot 'adler32.csv'  title 'Adler32'       with lines,\
     'crc32.csv'    title 'CRC32'         with lines,\
     'fnv.csv'      title 'FNV32'         with lines,\
     'hash.csv'     title 'Python hash'   with lines,\
     'md5.csv'      title 'MD5'           with lines,\
     'random.csv'   title 'Pseudo random' with lines,\
     'value.csv'    title 'BST'           with lines,
EOF

gnuplot << EOF
set terminal png medium size 800,600

set title  'Node depths histogram - comparision with AVL'
set ylabel 'frequency'
set xlabel 'depth'
set output 'histogram_avl.png'

plot 'fnv.csv'      title 'FNV32'         with lines,\
     'random.csv'   title 'Pseudo random' with lines,\
     'value.csv'    title 'BST'           with lines,\
     'avl.csv'      title 'AVL'           with lines
EOF
}


#gather_data
make_plots
