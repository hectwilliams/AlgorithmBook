#!/bin/bash

#
# Example: ./script 4 
# "Runs the 4th test in program"
#
#

g++ Solution.cpp -std=c++23   -fsyntax-only -Wall -Wextra -Wpedantic   &&  g++  -std=c++23  Solution.cpp  -o run  ; 

if (( $#  == 1 )) ; then 
    # printf "Error! Arugument required.\nTest Options:\n1: Test 1\n2: Test 2\n3: Test 3\n4: Test 4\n"
    ./run "$1"

else 
    echo "Tests"

    for i in {0..9}
    do
        if (( $i == 7)); then 
            continue 
        fi 
        response=$(./run $i)
        echo "$i: $response"
        
    done

        # ./run 0 &&  ./run 1


fi

# if [[ "$FRUIT" == "apple" ]]; then
#     echo "This is an apple."
# elif [[ "$FRUIT" == "banana" ]]; then
#     echo "This is a banana."
# else


