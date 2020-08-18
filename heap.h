#ifndef heap_h_
#define heap_h_
#include "ram.h"

typedef ram_cell_t heap_data_t; 
typedef struct{
    size_t elements;
    heap_data_t* arr;
};


#endif