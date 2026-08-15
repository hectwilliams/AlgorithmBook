#!/bin/bash

#
# Example: ./script 4 
# "Runs the 4th test in program"
#
#

if (( $#  != 1 )) ; then 
    printf "Error! Arugument required.\nTest Options:\n1: Test 1\n2: Test 2\n3: Test 3\n4: Test 4\n"
    exit 1
fi

g++ Solution.cpp -std=c++17   -fsyntax-only -Wall -Wextra -Wpedantic   &&  g++  -std=c++17  Solution.cpp  -o run  ; 

./run "$1"
