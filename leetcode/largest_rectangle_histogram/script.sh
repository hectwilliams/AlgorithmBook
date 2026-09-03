gcc -std=c99 largestRectangleArea.c  main.c -o run  ; 

if (( $#  == 1 )) ; then 
    ./run "$1"
fi
