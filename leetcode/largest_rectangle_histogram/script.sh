gcc -std=c99 -Wconversion  -fsanitize=address largestRectangleArea.c  main.c -o run  ; 

if (( $#  == 1 )) ; then 
    ./run "$1"
fi
