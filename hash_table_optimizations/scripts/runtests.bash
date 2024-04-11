#!/bin/bash

cd `dirname $0`

mkdir -p ../data/prof_results

valgrind --tool=callgrind --callgrind-out-file=../data/prof_results/callgring.out.no_opt --toggle-collect=HashTableFind ./no_opt.out < ../data/hash_table_test8-31.txt > /dev/null
valgrind --tool=callgrind --callgrind-out-file=../data/prof_results/callgring.out.opt1   --toggle-collect=HashTableFind ./opt1.out   < ../data/hash_table_test8-31.txt > /dev/null
valgrind --tool=callgrind --callgrind-out-file=../data/prof_results/callgring.out.opt2   --toggle-collect=HashTableFind ./opt2.out   < ../data/hash_table_test8-31.txt > /dev/null
valgrind --tool=callgrind --callgrind-out-file=../data/prof_results/callgring.out.opt3                                  ./opt3.out   < ../data/hash_table_test8-31.txt > /dev/null