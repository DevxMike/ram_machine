#ifndef ram_h
#define ram_h

#include <stdio.h>
typedef unsigned long long id_t;
typedef struct{
    id_t cell_id; //creating i.e. 3 "ram cells" is much better than not using 10000 ram cells  
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
inline int ram_is_empty(ram_chip_t* chip){
    return chip->quantity == 0;
}
inline int ram_is_full(ram_chip_t* chip){
    return chip->quantity == chip->chip_size;
}

void swap_structs(ram_cell_t*, ram_cell_t*);
#endif