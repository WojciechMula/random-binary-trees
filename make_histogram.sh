#!/bin/bash

count=10000
file="$1"

if [[ ! -f "$1" ]]
then
	echo "Usage: $0 filename"
	exit 1
fi

function gather_data {
	for name in adler32 crc32 fnv hash md5 random none
	do
		python main.py -f "$file" -k $name -l $count --csv-histogram=${name}.csv
	done

	for name in adler32 crc32 fnv hash md5 random none
	do
		python main.py -f "$file" -k $name -t earlyrotate -l $count --csv-histogram=${name}-early.csv
	done

	python main.py -f "$file" -k none -t avl -l $count --csv-histogram=avl.csv
}

function make_plots {
gnuplot << EOF
set terminal png medium size 800,600

set title  'Node depths histogram - BST'
set ylabel 'frequency'
set xlabel 'depth'
set output 'histogram.png'
set xrange [0:80]
set yrange [0:1600]

plot 'adler32.csv'  title 'Adler32'       with lines,\
     'crc32.csv'    title 'CRC32'         with lines,\
     'fnv.csv'      title 'FNV32'         with lines,\
     'hash.csv'     title 'Python hash'   with lines,\
     'md5.csv'      title 'MD5'           with lines,\
     'random.csv'   title 'Pseudo random' with lines,\
     'none.csv'     title 'N/A'           with lines,
EOF


gnuplot << EOF
set terminal png medium size 800,600

set title  'Node depths histogram - BST using "early rotate"'
set ylabel 'frequency'
set xlabel 'depth'
set output 'histogram_early_rotate.png'
set xrange [0:80]
set yrange [0:1600]

plot 'adler32-early.csv'  title 'Adler32'       with lines,\
     'crc32-early.csv'    title 'CRC32'         with lines,\
     'fnv-early.csv'      title 'FNV32'         with lines,\
     'hash-early.csv'     title 'Python hash'   with lines,\
     'md5-early.csv'      title 'MD5'           with lines,\
     'random-early.csv'   title 'Pseudo random' with lines,\
     'none-early.csv'     title 'N/A'           with lines,
EOF

gnuplot << EOF
set terminal png medium size 800,600

set title  'Node depths histogram - comparision with AVL'
set ylabel 'frequency'
set xlabel 'depth'
set output 'histogram_avl.png'

plot 'fnv.csv'          title 'FNV32'                 with lines,\
     'fnv-early.csv'    title 'FNV32 - early rotate'  with lines,\
     'none.csv'         title 'N/A'                   with lines,\
     'avl.csv'          title 'AVL'                   with lines
EOF
}

gather_data
make_plots
