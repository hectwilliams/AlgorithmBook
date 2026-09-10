gcc -std=c99 -Wconversion  -fsanitize=address readMem.c  main.c -o run  ; 

./run 

# if (( $#  == 1 )) ; then 
# fi
