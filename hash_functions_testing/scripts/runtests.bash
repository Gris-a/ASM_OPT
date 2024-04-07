#!/bin/bash

cd `dirname $0`

mkdir -p ../data/results/data
mkdir -p ../data/results/img

./hash.out 1 big < ../data/hash_functions_test.txt > ../data/results/data/ConstHash.txt
echo test 1 executed

./hash.out 2 big < ../data/hash_functions_test.txt > ../data/results/data/CharHash.txt
echo test 2 executed

./hash.out 3 big < ../data/hash_functions_test.txt > ../data/results/data/StrLenHash.txt
echo test 3 executed

./hash.out 4 big < ../data/hash_functions_test.txt > ../data/results/data/CheckSumHash.txt
./hash.out 4 small < ../data/hash_functions_test.txt > "../data/results/data/CheckSumHash(small).txt"
echo test 4 executed

./hash.out 5 big < ../data/hash_functions_test.txt > ../data/results/data/RotLHash.txt
echo test 5 executed

./hash.out 6 big < ../data/hash_functions_test.txt > ../data/results/data/RotRHash.txt
echo test 6 executed

./hash.out 7 big < ../data/hash_functions_test.txt > ../data/results/data/CRC32Hash.txt
echo test 7 executed

./plot.gpi