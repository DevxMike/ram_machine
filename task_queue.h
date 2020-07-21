#ifndef task_queue_h
#define task_queue_h
#include "stack.h"
#include <stdlib.h>

typedef stack_data_t task_queue_data_t;
typedef struct{
    size_t max;
    size_t quantity;
    task_queue_data_t* head, * tail;
}task_queue_t;

task_queue_t* task_queue_init(size_t size){
    task_queue_t* temp = NULL;
    if((temp = (task_queue_t*)malloc(sizeof(task_queue_t))) != NULL){
        temp->head = temp->tail = NULL;
        temp->max = size;
        temp->quantity = 0;
        return temp;
    }
    else{
        return NULL;
    }
}


#endif