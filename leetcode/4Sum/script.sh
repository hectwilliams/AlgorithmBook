#!/bin/bash

g++ Solution.cpp -std=c++17   -fsyntax-only -Wall -Wextra -Wpedantic   &&  g++  -std=c++17  Solution.cpp  -o run  ; 

./run "$1"
