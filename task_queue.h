#ifndef task_queue_h
#define task_queue_h
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

typedef stack_data_t task_queue_data_t; //for calls stack_data_t struct can be reused

typedef struct t{ //holds data and pointer to the next element
    task_queue_data_t data;
    struct t* next;
}task_queue_element_t;

typedef struct{ //holds general info about queue and pointer to head and it`s tail
    size_t max;
    size_t quantity;
    task_queue_element_t* head, * tail;
}task_queue_t;

task_queue_t* task_queue_init(size_t size);
bool task_queue_full(const task_queue_t* queue);
bool task_queue_empty(const task_queue_t* queue);

bool q_push(task_queue_t* queue, const task_queue_data_t* data);
void print_queue_status(task_queue_t* queue);
task_queue_data_t* q_pop(task_queue_t* queue);
#endif