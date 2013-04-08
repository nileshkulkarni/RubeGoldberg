#!/bin/bash
rm -rf data/
mkdir data
for i in $(seq 1 100) #iteration val
do
   for j in $(seq 1 100) #rerun num
   do
   		./bin/cs296_base $i > data/out-$i-$j.txt
   done
done
