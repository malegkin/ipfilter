#!/usr/bin/env bash -eu

for i in $(eval echo {0..$1}); 
do
    echo -e "$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256))\t$((RANDOM%100000))\t$((RANDOM%10000))"
done

