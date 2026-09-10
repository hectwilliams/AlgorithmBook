#include "readMem.h"

void readMem() {
    void *reader;
    int bytes;
    int read_number; 
    char *read_name =  malloc(NAME_SIZE_BYTES + 1);  // extra byte for stop flag (i.e. '\0')

    table_t my_table = {.count = 1, .name = "bobaac", .height= 199};

    bytes = sizeof(my_table);
    
    printf(" BYTE ALIGNED [%d bytes]\n", bytes); // aligned to largest data type attribute 

    reader = &my_table;

    // void *memcpy(void *dest, const void *src, size_t n);

    memcpy(&read_number, reader + OFFSET_COUNT, COUNT_SIZE_BYTES);
    printf("[ READ NUMBER %d ]\n", read_number);
    
    
    memcpy(read_name, reader + OFFSET_NAME,  NAME_SIZE_BYTES );
    read_name[NAME_SIZE_BYTES] = '\0'; // null character 
    printf("[ READ NAME %s ]\n", read_name);


    memcpy(&read_number, reader + OFFSET_HEIGHT,  HEIGHTS_SIZE_BYTES );
    printf("[ READ HEIGHT %d ]\n", read_number);

    

    free (read_name);

}

void readMemp() {
    void *reader;
    int bytes;
    int read_number; 
    char *read_name =  malloc(NAME_SIZE_BYTES + 1); 

    table_packed_t my_table = {.count = 1, .name = "123456", .height=9292};

    bytes = sizeof(my_table);
    
    printf(" PACKED [%d bytes]\n", bytes);

    reader = &my_table;

    memcpy(&read_number, reader + OFFSET_PACKED_COUNT, COUNT_SIZE_BYTES);
    printf("[ READ NUMBER %d ]\n", read_number);
    
    memcpy(read_name, reader + OFFSET_PACKED_NAME,  NAME_SIZE_BYTES );
    read_name[NAME_SIZE_BYTES] = '\0'; // null character 
    printf("[ READ NAME %s ]\n", read_name);
    
    memcpy(&read_number, reader + OFFSET_PACKED_HEIGHT,  HEIGHTS_SIZE_BYTES );
    printf("[ READ HEIGHT %d ]\n", read_number);


    // memcpy(&read_number, reader + OFFSET_COUNT, COUNT_SIZE_BYTES);
    // printf("[ READ NUMBER %d ]\n", read_number);
    
    
    // read_name[NAME_SIZE_BYTES] = '\0'; // null character 
    // memcpy(read_name, reader + OFFSET_NAME,  NAME_SIZE_BYTES );
    // printf("[ READ NAME %s ]\n", read_name);

    // free (read_name);

}