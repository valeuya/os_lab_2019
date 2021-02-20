#!/bin/bash
echo "There are $# arguments"
k=0
mod=0
for param in "$@";
do
    k=$[$k+$param]
done
total=$[$k/$#]
mod=$(($k%$#))
if [ "$mod" = "0" ]
then
echo The count is $#.
echo The sum is $k.
echo The average is $total.
else echo $total+$mod/$#
fi