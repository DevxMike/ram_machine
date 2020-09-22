#ifndef loop_pointers_h
#define loop_pointers_h
#include "loop_heap.h"

pointers_container_t* init_pointers(void);
void add_pointer(pointers_container_t*, loop_pointer_t*);
const loop_pointer_t* get_pointer(pointers_container_t*, char*);
void sort_pointers(pointers_container_t*, pointers_container_t*);

#endif