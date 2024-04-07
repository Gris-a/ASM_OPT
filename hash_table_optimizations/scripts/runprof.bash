#!/bin/bash

cd `dirname $0`

mkdir -p ../prof_results

valgrind --tool=callgrind --callgrind-out-file=../prof_results/callgring.out.no_opt --toggle-collect=HashTableInsert ./no_opt.out < ../data/hash_table_test.txt > /dev/null
valgrind --tool=callgrind --callgrind-out-file=../prof_results/callgring.out.opt1   --toggle-collect=HashTableInsert ./opt1.out   < ../data/hash_table_test.txt > /dev/null
valgrind --tool=callgrind --callgrind-out-file=../prof_results/callgring.out.opt2   --toggle-collect=HashTableInsert ./opt2.out   < ../data/hash_table_test.txt > /dev/null