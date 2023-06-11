#!/bin/bash

read -p "Taille du crible : " N
read -p "Nombre d'itérations : " iterations

for ((NUM_THREADS=1; NUM_THREADS<=7; NUM_THREADS++))
do
for (( i=1; i<=$iterations; i++ ))
do
  ./tache_3 $NUM_THREADS $N
done > time_exe.txt

sum=$(cat time_exe.txt | awk '{ sum += $1 } END { print sum }')
count=$(cat time_exe.txt | wc -l)
mean=$(echo "scale=7; $sum / $count" | bc)

echo "Mean exec, N = $N, $NUM_THREADS thread(s) --> $mean sec" >> output.txt
done