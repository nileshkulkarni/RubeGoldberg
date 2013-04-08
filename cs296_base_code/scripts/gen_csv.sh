#!/bin/bash
for i in $(seq 1 100) #rerun num
do
   for j in $(seq 1 100) #iteration val
   do
   		echo -n "$i," >>data/lab05_g28_data.csv
		sed 's/[a-z]//g' data/out-$j-$i.txt | sed 's/[A-Z]//g' | sed 's/://g' | sed 's/[  ]//g' > data/temp.txt
		while read line
		do
			echo -n "$line," >> data/lab05_g28_data.csv
		done < data/temp.txt
		echo -e -n "\n" >> data/lab05_g28_data.csv
		rm data/temp.txt
   done
done
