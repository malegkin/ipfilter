#!/usr/bin/env bash -eu

for i in {0..100}
do
    echo "$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256))"
done

