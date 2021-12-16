#include <stdio.h>
#include "buffer.h"

#define BITSPERBYTE 8
#define BUFSIZE sizeof(uint64_t)

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

    int8_t write_bit = -1;
    int8_t write_byte = -1;

    for (uint8_t write_bit_index = 0; write_bit_index < length; write_bit_index++) {   
        while (write_bit < start) {
            write_bit++;
            if (write_bit % BITSPERBYTE == 0)
                write_byte++;
        }
        
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
        while (read_bit < start) {
            read_bit++;
            if (read_bit % BITSPERBYTE == 0)
                read_byte++;
        }

        uint8_t bit = (buffer[read_byte] >> (read_bit % BITSPERBYTE) ) & 1;
        bits[read_bit_index] = bit ? 1 : 0;

        read_bit++;
        if (read_bit % BITSPERBYTE == 0)
            read_byte++;
    }

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