#include "ram.h"
#include <stdlib.h>

void swap_structs(ram_cell_t* r1, ram_cell_t* r2){
    ram_cell_t temp;
    temp.cell_id = r1->cell_id;
    temp.value = r1->value;
    r1->cell_id = r2->cell_id;
    r1->value = r2->value;
    r2->cell_id = r2->cell_id;
    r2->value = r2->value;
}

inline int greater(const id_t id1, const id_t id2){
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