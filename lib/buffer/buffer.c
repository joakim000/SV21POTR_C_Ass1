#include <stdio.h>

#include "buffer.h"

// #define DEBUG

#define BITSPERBYTE 8
#define BUFSIZE sizeof(uint64_t)

#ifdef DEBUG
void i82p(uint8_t nums[], size_t size, size_t cropTo, char separator, int newline){
    if (cropTo == 0)
        cropTo = size;
    for (int i = size - cropTo; i < size; i++)
        if (i < size - 1)
            printf("%d%c", nums[i], separator);
        else 
            printf("%d", nums[i]);
    for (int i = 0; i < newline; i++)
        printf("\n");
}
#endif

void buffer_insert(uint8_t *buffer, uint8_t start, uint8_t length, uint64_t value) {
    void const * const ptr = &value;
    uint8_t bits[sizeof value * BITSPERBYTE] = {0};
    int  byte_index, 
         bit_index;
    uint8_t *byte = (uint8_t*) ptr;
    uint8_t bit;

    for (byte_index = 0; byte_index < sizeof value; byte_index++)         // LSF
        for (bit_index = 0; bit_index < 8; bit_index++) {                 // LSF
            bit = (byte[byte_index] >> bit_index) & 1;
            bits[byte_index * 8 + bit_index] = bit ? 1 : 0;
        }
    #ifdef DEBUG
    i82p(bits, length, 0, 0, 1);
    #endif

    int8_t write_bit = -1;
    int8_t write_byte = -1;
    #ifdef DEBUG
    printf("b4 write forloop. bit_index:%d write_bit:%d write_byte:%d\n", bit_index, write_bit, write_byte);
    #endif

    for (uint8_t write_bit_index = 0; write_bit_index < length; write_bit_index++) {   
        #ifdef DEBUG
        printf("write forloop b4 while. write_bit_index:%d write_bit:%d \n", write_bit_index, write_bit);
        #endif

        while (write_bit < start) {
            write_bit++;
            if (write_bit % BITSPERBYTE == 0)
                write_byte++;
            #ifdef DEBUG        
            printf("write while. bit_index:%d write_bit:%d write_byte:%d\n", write_bit_index, write_bit, write_byte);
            #endif
        }
        
        #ifdef DEBUG
        printf("write forloop after while. bit_index:%d write_bit:%d write_byte:%d\n", write_bit_index, write_bit, write_byte);
        #endif

        if (bits[write_bit_index]) 
            // OR 1 with bit at index means 1
            buffer[write_byte] |= 1ULL << (write_bit % BITSPERBYTE);
        else
            // AND with NOT of bit at index means 0
            buffer[write_byte] &= ~( 1ULL << (write_bit % BITSPERBYTE) );

        write_bit++;
        if (write_bit % BITSPERBYTE == 0)
            write_byte++;
    }
}

uint64_t buffer_extract(uint8_t *buffer, uint8_t start, uint8_t length) {
    uint8_t bits[length];
    int8_t read_bit = -1;
    int8_t read_byte = -1;

    for (uint8_t read_bit_index = 0; read_bit_index < length; read_bit_index++) {   
        #ifdef DEBUG
        printf("read forloop b4 while. read_bit_index:%d read_bit:%d \n", read_bit_index, read_bit);
        #endif

        while (read_bit < start) {
            read_bit++;
            if (read_bit % BITSPERBYTE == 0)
                read_byte++;
            #ifdef DEBUG        
            printf("read while. bit_index:%d read_bit:%d read_byte:%d\n", read_bit_index, read_bit, read_byte);
            #endif
        }
        
        #ifdef DEBUG
        printf("read forloop after while. bit_index:%d read_bit:%d read_byte:%d\n", read_bit_index, read_bit, read_byte);
        #endif

        uint8_t bit = (buffer[read_byte] >> (read_bit % BITSPERBYTE) ) & 1;
        bits[read_bit_index] = bit ? 1 : 0;

        read_bit++;
        if (read_bit % BITSPERBYTE == 0)
            read_byte++;
    }

    #ifdef DEBUG
    i82p(bits, length, 0, 0, 1);
    #endif

    uint64_t r = 0;
    for (uint8_t r_bit_index = 0; r_bit_index < length; r_bit_index++) {   
        if (bits[r_bit_index]) 
            // OR 1 with bit at index means 1
            r |= 1ULL << (r_bit_index);
        else
            // AND with NOT of bit at index means 0
            r &= ~(1ULL << (r_bit_index) );
    }
    return r; 
}



