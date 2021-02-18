#!/bin/bash
exec 0<numbers.txt 
count=1
k=0
while read param;do
    k=$[$k+$param]
    count=$(( $count + 1 ))
done < numbers.txt
total=$[$k/$count]
echo The count is $count.
echo The sum is $k.
echo The average is $total.
