#ifndef heap_h_
#define heap_h_
#include "ram.h"

typedef ram_cell_t heap_data_t; 
typedef struct{
    size_t elements;
    size_t heap_size;
    heap_data_t* arr;
}heap_t;

void h_push(heap_t*, const heap_data_t*, unsigned*);
heap_data_t* h_pop(heap_t*);
heap_t* init_heap(void);

inline int heap_empty(const heap_t* heap){
    return heap->elements == 0;
}
inline int heap_full(const heap_t* heap){
    return heap->elements == heap->heap_size;
}
#endif