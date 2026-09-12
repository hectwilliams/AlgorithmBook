
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
    // int * const heights; // fixed pointer location 
    int const * heights; // dynamic pointer location ; cannot modify (i.e. deref
    int const * len; // dynamic pointer location ; cannot modify (i.e. deref

    if (code1 | code2) {
        return 1;
    }
    
    switch (test_id ){
        
        case 1:
            heights = test_vector_1;
            len = &test_vector_1_len;
            break;

        case 2:
            heights = test_vector_2;
            len = &test_vector_2_len;
            break;

        case 3:
            heights = test_vector_3;
            len = &test_vector_3_len;
            break;

        case 4:
            heights = test_vector_4;
            len = &test_vector_4_len;
            break;
        
        case 5:
            heights = test_vector_5;
            len = &test_vector_5_len;
            break;

        case 6:
            heights = test_vector_6;
            len = &test_vector_6_len;
            break;

        case 7:
            heights = test_vector_7;
            len = &test_vector_7_len;
            break;

        case 8: 
            heights = test_vector_8;
            len = &test_vector_8_len;
            break;

        case 9: 
            heights = test_vector_9;
            len = &test_vector_9_len;
            break;

        case 10: 
            heights = test_vector_10;
            len = &test_vector_10_len;
            break;


        case 11: 
            heights = test_vector_11;
            len = &test_vector_11_len;
            break;


        case 12: 
            heights = test_vector_12;
            len = &test_vector_12_len;
            break;


        case 13: 
            heights = test_vector_13;
            len = &test_vector_13_len;
            break;

        case 14: 
            heights = test_vector_14;
            len = &test_vector_14_len;
            break;

        case 15: 
            heights = test_vector_15;
            len = &test_vector_15_len;
            break;

        case 16: 
            heights = test_vector_16;
            len = &test_vector_16_len;
            break;

        case 17: 
            heights = test_vector_17;
            len = &test_vector_17_len;
            break;

        case 18: 
            heights = test_vector_18;
            len = &test_vector_18_len;
            break;
        

        case 19: 
            heights = test_vector_19;
            len = &test_vector_19_len;
            break;

        default:
            break;
        
    }
    
    struct timespec start_struct, end_struct;

    clock_gettime(CLOCK_MONOTONIC, &start_struct);

    int result = largestRectangleArea( ( int *)  heights, *len);

    // int result = -1;
    clock_gettime(CLOCK_MONOTONIC, &end_struct);

    double time_taken = (end_struct.tv_sec - start_struct.tv_sec) +  (end_struct.tv_nsec - start_struct.tv_nsec) / 1e9;

    printf("Elapsed time: %f seconds\n", time_taken);

    printf(" result: (%d) \n", result);

    // return 0;

}