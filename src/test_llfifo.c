#include "test_llfifo.h"
#include "llfifo.h"
#include <stdio.h>
#include <assert.h>



int test_llfifo(){
    printf("\n\n Testing LLFIFO \n\n");    

    // if NULL ptr passed return NULL
    int invalid_cap = -1;
    llfifo_t* error_q = llfifo_create(invalid_cap);
    assert(error_q == NULL);
    llfifo_destroy(error_q); 

    // enqueue error testing
    int cap = 5;
    llfifo_t* testingq = llfifo_create(cap);
    assert(testingq != NULL);
    int* null_ptr = NULL;
    int items_added = llfifo_enqueue(testingq, null_ptr);
    assert(items_added  == -1); // error value
    llfifo_destroy(testingq); 

    // dequeue error
    int valid_val = 8;
    int * pvalid_val = &valid_val;
    testingq = llfifo_create(cap);
    assert(testingq != NULL);
    items_added = llfifo_enqueue(testingq, pvalid_val);
    validate_llfifo(testingq); // debug message in case of assertion failure
    assert(items_added == 1); // error when dequed on empty
    int * items_removed_1 = (int *)llfifo_dequeue(testingq);
    int * items_removed_2 = (int *)llfifo_dequeue(testingq);
    assert(items_removed_1 != NULL); // error when dequed on empty
    assert(items_removed_2 == NULL); // error when dequed on empty
    llfifo_destroy(testingq); 

    // length and capacity test (and testing increase)
    testingq = llfifo_create(cap);
    for (int i=0; i<10; i++)
        items_added = llfifo_enqueue(testingq, pvalid_val);
    validate_llfifo(testingq); // debug message in case of assertion failure
    assert(llfifo_length(testingq) == 10);
    assert(llfifo_capacity(testingq) == 10);

    // capacity of size  0
    int cap_1 = 0;
    llfifo_t* llQ = llfifo_create(cap_1);
    assert(llQ != NULL);
    validate_llfifo(llQ);
    assert(llfifo_capacity(llQ) == cap_1);
    llfifo_destroy(llQ);
    //validate_llfifo(llQ);

    // capacity of size  10
    int cap_2 = 5;
    llfifo_t* llQ2 = llfifo_create(cap_2);
    assert(llQ2 != NULL);
    validate_llfifo(llQ2);
    assert(llfifo_capacity(llQ2) == cap_2);
    llfifo_destroy(llQ2);
    //validate_llfifo(llQ2);

    // 2 QUEUES
    double value = 500000000000000;
    double* pvalue = &value;
    llfifo_t* llQ3 = llfifo_create(cap_2);
    llfifo_t* llQ4 = llfifo_create(cap_2);
    assert(llQ3 != NULL);
    assert(llQ4 != NULL);
    llfifo_enqueue(llQ3, pvalue);
    validate_llfifo(llQ4);
    llfifo_enqueue(llQ4, pvalue);
    validate_llfifo(llQ4);
    llfifo_enqueue(llQ4, pvalue);
    validate_llfifo(llQ4);
    llfifo_destroy(llQ3);
    llfifo_destroy(llQ4);

    // capacity of size  1
    int cap_3 = 1;
    llfifo_t* llQ5 = llfifo_create(cap_3);
    assert(llQ5 != NULL);
    validate_llfifo(llQ5);
    assert(llfifo_capacity(llQ5) == cap_3);
    llfifo_destroy(llQ5);

    // capacity of size  20
    int cap_4 = 20;
    llfifo_t* llQ6 = llfifo_create(cap_4);
    assert(llQ6 != NULL);
    validate_llfifo(llQ6);
    assert(llfifo_capacity(llQ6) == cap_4);
    llfifo_destroy(llQ6);


    // testing memory free
    llfifo_t* llQ7 = llfifo_create(cap_4);
    assert(llQ7 != NULL);
    validate_llfifo(llQ7);
    assert(llfifo_capacity(llQ7) == cap_4);
    llfifo_enqueue(llQ7, pvalue);
    validate_llfifo(llQ7);
    llfifo_destroy(llQ7);
    assert(llfifo_memory_used(llQ7) == llfifo_memory_freed(llQ7));

    // return 0 upon success
    return 0;
}