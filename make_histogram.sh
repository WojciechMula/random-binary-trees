#!/bin/bash

count=10000
file="$1"

if [[ ! -f "$1" ]]
then
	echo "Usage: $0 filename"
	exit 1
fi

for name in adler32 crc32 fnv hash md5 random value
do
	python main.py -f "$1" -k $name -l $count --csv-histogram=${name}.csv
done

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
     'value.csv'    title 'Value'         with lines
EOF
