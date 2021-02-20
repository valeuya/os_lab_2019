#!/bin/bash
exec 0<numbers.txt 
count=1
k=0
while read param;do
    k=$[$k+$param]
    count=$(( $count + 1 ))
done < numbers.txt
total=$[$k/$count]
mod=$(($k%$count))
echo The count is $count.
echo The sum is $k.
if [ "$mod" = "0" ]
then
echo The average is $total.
else echo $total+$mod/$count
fi
