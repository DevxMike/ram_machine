#ifndef ram_heap_h_
#define ram_heap_h_
#include "ram.h"

typedef ram_cell_t ram_heap_data_t; 
typedef struct{
    size_t elements;
    size_t ram_heap_size;
    ram_heap_data_t* arr;
}ram_heap_t;

int ram_heap_push(ram_heap_t*, const ram_heap_data_t*, unsigned*);
void ram_heap_pop(ram_heap_t*, ram_chip_t*);
ram_heap_t* init_ram_heap(void);
int ram_heap_empty(const ram_heap_t*);
int ram_heap_full(const ram_heap_t*);
void ram_shift_up(ram_heap_t*, size_t);
void ram_shift_down(ram_heap_t*, size_t, size_t, size_t);
int greater(const id_type, const id_type);
void copy_ram_heap(ram_heap_t*, const ram_heap_t*);
void ram_heap_sort(ram_heap_t*, const ram_heap_t*, ram_chip_t*);
#endif