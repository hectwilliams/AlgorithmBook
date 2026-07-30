#!/bin/bash

#
# 
#
#
#

if (( $#  != 1 )) ; then 
    printf "Error! Arugument required.\nTest Options:\n1: Test 1n"
    exit 1
fi

g++ Solution.cpp -std=c++17   -fsyntax-only -Wall -Wextra -Wpedantic   &&  g++  -std=c++17  Solution.cpp  -o run  ; 

./run "$1"
