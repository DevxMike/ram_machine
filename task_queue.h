#ifndef task_queue_h
#define task_queue_h
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

typedef stack_data_t task_queue_data_t;

typedef struct t{
    task_queue_data_t data;
    struct t* next;
}task_queue_element_t;

typedef struct{
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