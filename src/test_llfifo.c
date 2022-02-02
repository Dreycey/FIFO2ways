#include "test_llfifo.h"
#include "llfifo.h"
#include <stdio.h>


int test_llfifo(){
    printf("\n\n Testing LLFIFO \n\n");

    // capacity of size  0
    int cap_1 = 0;
    llfifo_t* llQ = llfifo_create(cap_1);
    validate_llfifo(llQ);
    llfifo_destroy(llQ);
    validate_llfifo(llQ);

    // capacity of size  10
    int cap_2 = 10;
    llfifo_t* llQ2 = llfifo_create(cap_2);
    validate_llfifo(llQ2);
    llfifo_destroy(llQ2);
    validate_llfifo(llQ2);

    // 2 QUEUES
    double value = 500000000000000;
    double* pvalue = &value;
    llfifo_t* llQ3 = llfifo_create(cap_2);
    llfifo_t* llQ4 = llfifo_create(cap_2);
    llfifo_enqueue(llQ3, pvalue);
    validate_llfifo(llQ3);
    llfifo_enqueue(llQ3, pvalue);
    validate_llfifo(llQ3);
    llfifo_enqueue(llQ4, pvalue);
    validate_llfifo(llQ4);
    llfifo_destroy(llQ3);
    llfifo_destroy(llQ4);

    // return 0 upon success
    return 0;
}