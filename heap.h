#ifndef heap_h_
#define heap_h_
#include "ram.h"

typedef ram_cell_t heap_data_t; 
typedef struct{
    size_t elements;
    size_t heap_size;
    heap_data_t* arr;
}heap_t;

int h_push(heap_t*, const heap_data_t*, unsigned*);
void h_pop(heap_t*, ram_chip_t*);
heap_t* init_heap(void);
int heap_empty(const heap_t*);
int heap_full(const heap_t*);
void shift_up(heap_t*, size_t);
void shift_down(heap_t*, size_t, size_t, size_t);
int greater(const id_type, const id_type);
#endif