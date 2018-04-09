#!/bin/bash

for arg in "$@"
do
    case $arg in
        "0" )
            cat "$1" | cut -f1 | sort -n -r -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 ;;
        "1" )
            cat "$1" | cut -f1 | sort -n -r -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 | awk '{split($0 , oct , "."); if (oct[1] == '1') print $0;}' ;;
        "2" )
            cat "$1" | cut -f1 | sort -n -r -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 | awk '{split($0 , oct , "."); if (oct[1] == '46' && oct[2] == '70') print $0;}' ;;
        "3" )
            cat "$1" | cut -f1 | sort -n -r -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 | awk '{split($0 , oct , "."); if (oct[1] == '46' || oct[2] == '46' || oct[3] == '46' || oct[4] == '46') print $0;}'

   esac
done

