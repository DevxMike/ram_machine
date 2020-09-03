#ifndef loop_heap_h
#define loop_heap_h
#include "loop.h"
#include <stdio.h>

typedef struct{
    loop_t* arr;
    size_t size;
    size_t quantity;
}loop_heap_t;

loop_heap_t* init_loop_heap(void);
void loop_heap_push(loop_heap_t*, const loop_t*);
loop_t* loop_heap_pop(loop_heap_t*);
int loop_heap_empty(const loop_heap_t*);
int loop_heap_full(const loop_heap_t*);
#endif