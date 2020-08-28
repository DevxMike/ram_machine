#ifndef task_queue_h
#define task_queue_h
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define CMD_SIZE 10
#define OP_SIZE 11

typedef struct { //struct used to hold commands and operands
    int cmd_id;
    char command[CMD_SIZE];
    char operand_st[OP_SIZE];
}task_queue_data_t;

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
void copy_data_struct(task_queue_data_t* destination, const task_queue_data_t* source);
#endif