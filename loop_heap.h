#ifndef loop_heap_h
#define loop_heap_h
#include "loop.h"
#include <stdio.h>

typedef struct{
    loop_t* arr;
    size_t size;
    size_t quantity;
}loop_heap_t;

typedef struct{
    loop_t* pointer;
    task_queue_element_t* next_cmd;
}loop_pointer_t;

typedef struct{
    loop_pointer_t** arr;
    size_t max, quantity;
}pointers_container_t;

typedef struct{
    loop_heap_t* heap;
    loop_container_t* loops_array;
    loop_t* temp_loop;
    pointers_container_t* loop_pointers, * pointers_heap;
}main_loop_type_t;

loop_heap_t* init_loop_heap(void);
void loop_heap_push(loop_heap_t*, const loop_t* const);
loop_t* loop_heap_pop(loop_heap_t*);
int loop_heap_empty(const loop_heap_t*);
int loop_heap_full(const loop_heap_t*);
void add_to_loop_container(loop_container_t*, loop_t*, loop_heap_t*);
void loop_heap_sort(loop_container_t*, loop_heap_t*);
#endif