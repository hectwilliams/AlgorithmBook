
#include "largestRectangleArea.h" 


int main(int param_count, char *args[]) {

    if (param_count != 2) {
        
        return 1;
        
    }
    
    errno = 0; 

    char *endptr;
    long test_id = strtol(args[1], &endptr, 10);
    int code1 = test_conv_str(test_id);
    int code2 = test_digit_found( args[1], endptr);
    int heights[] = {2,1,5,6,2,3};

    struct timespec start_struct, end_struct;

    clock_gettime(CLOCK_MONOTONIC, &start_struct);

    int result = largestRectangleArea(heights, sizeof(heights) / sizeof(int));
    
    clock_gettime(CLOCK_MONOTONIC, &end_struct);

    double time_taken = (end_struct.tv_sec - start_struct.tv_sec) +  (end_struct.tv_nsec - start_struct.tv_nsec) / 1e9;

    printf("Elapsed time: %f seconds\n", time_taken);

    printf(" ( %d ) ( %d )\t result: (%d) \n", code1, code2, result);

    return 0;

}