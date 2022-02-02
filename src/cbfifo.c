#include "cbfifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define CB_SIZE 128 // size of buffer


/* 
 * circular buffer
 * from Ch. 6 White
 */
struct sCircularBuffer {
  uint8_t array[CB_SIZE];    // must be a power of two
  int read;    // holds current read position: 0 to (CB_SIZE-1)
  int write;   // holds current write position: 0 to (CB_SIZE-1)
  int length; // Default is 0, changed to true once full.
};

/* 
 * Creating a typedef for the circular buffer
 */
typedef struct sCircularBuffer tCircularBuffer;

/* 
 * Instantiating static ciric buff 
 */
static tCircularBuffer cb;

size_t cbfifo_enqueue(void *buf, size_t nbyte) {
    if (nbyte < 0) {return (CB_SIZE-1);}
    if (!buf) {return (CB_SIZE-1);}

    int num_bytes_added = 0;
    uint8_t * ptr_to_buffer = buf;
    for (int i=0; i < nbyte; i++){
        if (cb.length >= CB_SIZE) {return num_bytes_added;}
        cb.array[cb.write] = (*(uint8_t *)ptr_to_buffer) & (0xFF);
        cb.length++;
        num_bytes_added++;
        ptr_to_buffer++;

        // update the write pointer - resets to zero once == CB_SIZE
        cb.write = (cb.write + 1) & (CB_SIZE - 1);
    }
    return num_bytes_added;
}

size_t cbfifo_dequeue(void *buf, size_t nbyte) {

    uint8_t * ptr_cpy = (uint8_t *)buf;
    int num_bytes_removed = 0;
    if (cb.length <= 0) {return num_bytes_removed;}
    for (int i=0; i<nbyte; i++){
        if (cb.length <= 0) {return num_bytes_removed;} // if empty, return
        ptr_cpy[i] = cb.array[cb.read];
        cb.length--;
        num_bytes_removed++;

        // update the write pointer - resets to zero once == CB_SIZE
        cb.read= (cb.read + 1) & (CB_SIZE - 1);
    }
    return num_bytes_removed;
}

int validate_dbfifo() {
    int read_cpy = cb.read;
    printf("\n\n CBFIFO Validation \n");
    printf("\t Read ptr: %d Write ptr: %d \n", cb.read, cb.write);
    printf("\t length: %ld capacity: %ld \n", cbfifo_length(), cbfifo_capacity());
    for (int index=0; index < cbfifo_length(); index++) {
        printf("\t value at array index: %d is %d \n", read_cpy, cb.array[read_cpy]);
        read_cpy = (read_cpy + 1) & (CB_SIZE - 1);
    }
    return 0;
}

size_t cbfifo_capacity() {
    return CB_SIZE;
}

size_t cbfifo_length() {
    return cb.length;
}