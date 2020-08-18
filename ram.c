#include "ram.h"
#include <stdlib.h>

int ram_is_empty(ram_chip_t* chip){
    return chip->quantity == 0;
}
int ram_is_full(ram_chip_t* chip){
    return chip->quantity == chip->chip_size;
}

void swap_structs(ram_cell_t* r1, ram_cell_t* r2){
    ram_cell_t temp;

    copy_structs(&temp, r1);
    copy_structs(r1, r2);
    copy_structs(r2, &temp);
}

inline int greater(const id_type id1, const id_type id2){
    return id1 > id2;
}
ram_chip_t* init_ram(){
    ram_chip_t* temp = NULL;
    if((temp = (ram_chip_t*) malloc(sizeof(ram_cell_t))) != NULL){
        temp->chip_size = 1;
    }

    return temp;
}
void ram_push(ram_chip_t* r_chip, const ram_cell_t* r_cell){
    //to do
}
ram_cell_t* ram_pop(ram_chip_t* chip){
    return NULL; //to do
}
void copy_structs(ram_cell_t* destination, const ram_cell_t* const source){
    destination->cell_id = source->cell_id;
    destination->value = source->value;
}