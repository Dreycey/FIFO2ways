#include "test_cbfifo.h"
#include "cbfifo.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


int test_cbfifo() {
    printf("\n\n Testing CBFIFO \n\n");

    // Testing my name
    char val_to_store[] = {'D', 'r', 'e', 'y', 'c', 'e', 'y', '\0'}; 
    size_t number_added = cbfifo_enqueue(val_to_store, sizeof(val_to_store));
    printf("number added: %ld \n", number_added);
    char my_name[sizeof(val_to_store)];
    cbfifo_dequeue(my_name, sizeof(val_to_store));
    printf("NAME POINTER: %p \n", my_name);
    printf("My name, dequed, is: %s \n", my_name);
    printf("Value stored: %s \n", val_to_store);
    assert(strcmp(my_name, val_to_store) == 0);
    validate_dbfifo();

    // testing a dequeue with an empty queue
    assert(cbfifo_dequeue(my_name, sizeof(val_to_store)) == 0);

    // Add 128 (max) PLUS ONE
    char single_char[] = {'A'};
    int max_size = 128;
    for (int i=1; i<=max_size; i++) {
        number_added = cbfifo_enqueue(single_char, 1);
    }
    number_added = cbfifo_enqueue(single_char, 1);
    printf("number added: %ld \n", number_added);
    assert(number_added == 0); // should be one less than max

    // return 0 if all pass
    return 0;
}