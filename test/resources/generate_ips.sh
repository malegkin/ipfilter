#!/usr/bin/env bash -eu

for ((ip=0; ip<=$1; ip++))
do
    echo "$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256))"
done

