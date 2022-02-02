#include "llfifo.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * node - individual node in the linked list
 */
struct Node {
    void* data;
    struct Node* next;
};

/* 
 * llfifo_s - the definition for the linked list structure
 */
struct llfifo_s {
    int initial_capacity;
    int capacity;
    int length;
    struct Node* head;
    int malloc_calls;
    int free_calls;
};

/* check header for usage */
int llfifo_memory_used(llfifo_t * llQ) {
    return llQ->malloc_calls;
}

/* check header for usage */
int llfifo_memory_freed(llfifo_t * llQ) {
    return llQ->free_calls;
}

/* check header for usage */
llfifo_t *llfifo_create(int capacity) {
    if (capacity < 0) {return NULL;}

    llfifo_t* llQueue = (llfifo_t*)malloc(sizeof(llfifo_t));
    if (llQueue == NULL) {return NULL;} // If Null ptr returned
    llQueue->capacity = capacity;
    llQueue->initial_capacity = capacity;
    llQueue->length = 0;
    llQueue->head = (struct Node *)malloc(sizeof(struct Node) * (capacity)); //init size
    llQueue->malloc_calls++;
    //if (llQueue->head == NULL) {return NULL;} // If Null ptr returned

    /* Build initial Linked List*/
    int counter = 1;
    struct Node* ptr = llQueue->head;
    struct Node* prev_node = llQueue->head;
    prev_node->next = NULL;
    while (counter < capacity) {
        struct Node* curr_node = &ptr[counter];
        prev_node->next = curr_node;
        prev_node = curr_node;
        prev_node->next = NULL;
        counter++;
    }
    /* Build initial Linked List*/

    return llQueue;
}

/* check header for usage */
int llfifo_enqueue(llfifo_t *fifo, void *element) {
    if (element == NULL) {return -1;}

    struct Node* node = fifo->head;
    if (fifo->capacity > fifo->length) {
        int counter = 0;
        while (counter < fifo->length) {
            node = node->next;
            counter++;
        }
        node->data = element; /* TODO: How to save element? just a pointer? */
        fifo->length++;
    }
    else {
        struct Node* curr_node = (struct Node *)malloc(sizeof(struct Node));
        fifo->malloc_calls++;
        // add new node to end of linked list
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = curr_node;
        curr_node->next = NULL;
        curr_node->data = element; /* TODO: How to save element? just a pointer? */
        fifo->length++;
        fifo->capacity++;
    }
    return fifo->length;
}

/* check header for usage */
void *llfifo_dequeue(llfifo_t *fifo) {
    if (fifo->length == 0) {return NULL;} // if empty
    struct Node* prev_node;
    struct Node* node = fifo->head;
    void * result_ptr = node->data; // head is oldest data
    /* SHIFT UP LINKED LIST O(N) */ 
    while (node->next != NULL){
        prev_node = node;
        node = node->next;
        prev_node->data = node->data;
    }
    if (node->next == NULL) {node->data = NULL;} // last must be NULL on dequeue
    fifo->length--;
    return result_ptr;  
}

/* check header for usage */
int llfifo_length(llfifo_t *fifo) {
    return fifo->length;
}

/* check header for usage */
int llfifo_capacity(llfifo_t *fifo) {
    return fifo->capacity;
}

/* check header for usage */
void llfifo_destroy(llfifo_t *fifo) {
    if (fifo == NULL) // if null ptr
        return;
    struct Node* node = fifo->head;
    struct Node* prev_node;
    int count = 0;
    while (node != NULL){
        prev_node = node;
        node = node->next;
        if (count > fifo->initial_capacity) {
            free(prev_node);
            fifo->free_calls++;
        }
        count++;
    }
    if (fifo->head != NULL) {
        free(fifo->head); // Free initial cacpacity allocted last
        fifo->free_calls++;
    }
    free(fifo);
}

/* check header for usage */
int validate_llfifo(llfifo_t* llQ){
    printf("\n\nINFORMATION ON THE LLFIFO \n");
    printf("\t 1. Here is the current length: %d \n", llQ->length);
    printf("\t 2. Here is the current capacity: %d \n", llQ->capacity);
    int node_count = 0;
    struct Node* node = llQ->head;
    while (node != NULL){
        printf("\t Data at node %d is %p \n", node_count, node->data);
        node = node->next;
        node_count += 1;
    }
    return 0;
}

