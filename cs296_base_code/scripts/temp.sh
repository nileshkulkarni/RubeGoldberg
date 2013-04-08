#!/bin/bash
cnt=0;
while read line
do
	let cnt=cnt+1; 
  	if [ $(($cnt % 100)) -eq 7 ]; 
    	then echo "$line" >> data/lab05_g28_data_temp.csv;
	fi;
done < data/lab05_g28_data.csv
