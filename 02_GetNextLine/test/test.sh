#!/bin/bash

# Define colors
C_RED='\033[0;31m'
C_BLUE='\033[0;34m'
C_GREEN='\033[0;32m'
C_NC='\033[0m'

clear

echo -e "${C_BLUE}GNL TESTS by werodrig."
echo -e "${C_BLUE}Filename\t1\t2\t3\t4\t5\t10\t20\t100\t1000\t10000${C_NC}"

for file in *.txt; do

    echo -ne "${file}\t"

    for buffer_size in 1 2 3 4 5 10 20 100 1000 10000; do

        cc test_maker.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=$buffer_size -o a.out

        if [ $? -ne 0 ]; then
            echo -ne "💔"
            continue
        fi

        ./a.out "$(printf "%s" "$file")"

        diff -q "$file" __output.txt > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo -ne "\t${C_RED}✘${C_NC}"
        else
            echo -ne "\t${C_GREEN}✔${C_NC}"
        fi

        rm -f a.out
        rm -f __output.txt
    done
    echo -e ""
done

echo -e "\n"