#ifndef ram_h
#define ram_h

#include <stdio.h>
typedef unsigned long long id_type;

typedef struct{
    id_type cell_id; //creating i.e. 3 "ram cells" is much better than not using 10000 ram cells  
    int value; //value to be hold
}ram_cell_t;

typedef struct{
    size_t quantity;
    size_t chip_size; //quantity of ram cells used in user`s algorithm
    ram_cell_t* arr; //array of "ram cells"
}ram_chip_t;

ram_chip_t* init_ram();
void ram_push(ram_chip_t*, const ram_cell_t*);
ram_cell_t* ram_pop(ram_chip_t*);
void copy_structs(ram_cell_t*, const ram_cell_t* const);
void swap_structs(ram_cell_t*, ram_cell_t*);
int ram_is_empty(ram_chip_t* chip);
int ram_is_full(ram_chip_t* chip);



void swap_structs(ram_cell_t*, ram_cell_t*);
#endif