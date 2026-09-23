gcc -std=c99 -Wconversion  -fsanitize=address  main.c -o main  ; 

if (( $#  == 1 )) ; then 
    ./main "$1"
else 
    echo "wtf" 
fi
