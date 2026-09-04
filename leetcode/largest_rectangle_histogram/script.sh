gcc -std=c99 -fsanitize=address largestRectangleArea.c  main.c -o run  ; 

if (( $#  == 1 )) ; then 
    ./run "$1"
fi
