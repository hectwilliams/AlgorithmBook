#!/bin/bash

g++ Solution.cpp -std=c++17   -fsyntax-only -Wall -Wextra -Wpedantic   &&  g++  -std=c++17 run.cpp Solution.cpp -o run  ; ./run
