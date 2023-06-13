#!/bin/bash

read -p "Taille du crible : " N
read -p "Nombre d'itérations : " iterations

>output_files/time_exe_seq.txt
>output_files/output_seq.txt

for (( i=1; i<=$iterations; i++ ))
do
  ./tache_2 $N
done > output_files/time_exe_seq.txt

sum=$(cat output_files/time_exe_seq.txt | awk '{ sum += $1 } END { print sum }')
count=$(cat output_files/time_exe_seq.txt | wc -l)
mean=$(echo "scale=7; $sum / $count" | bc)

echo "Mean exec, N = $N, --> $mean sec" >> output_files/output_seq.txt