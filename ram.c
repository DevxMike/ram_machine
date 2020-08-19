#include "ram.h"
#include <stdlib.h>

int ram_empty(ram_chip_t* chip){
    return chip->quantity == 0;
}
int ram_full(ram_chip_t* chip){
    return chip->quantity == chip->chip_size;
}

void swap_structs(ram_cell_t* r1, ram_cell_t* r2){
    ram_cell_t temp;

    copy_structs(&temp, r1);
    copy_structs(r1, r2);
    copy_structs(r2, &temp);
}

int ram_search(const id_type target, const ram_chip_t* chip, size_t left, size_t right, size_t mid){
    if(chip->arr[mid].cell_id == target){
        return mid;
    }
    else if(chip->arr[mid].cell_id > target){
        return ram_search(target, chip, mid, right, (mid+right)/2);
    }
    else if(chip->arr[mid].cell_id < target){
        return ram_search(target, chip, left, mid, (left+mid)/2);
    }
    else{
        return -1;
    }
}

ram_chip_t* init_ram(){
    ram_chip_t* temp = NULL;
    
    if((temp = (ram_chip_t*) malloc(sizeof(ram_chip_t))) != NULL){
        if((temp->arr = (ram_cell_t*)malloc(sizeof(ram_cell_t))) == NULL){
            return NULL;
        }
        temp->chip_size = 1;
        temp->quantity = 0;
    }

    return temp;
}
int ram_push(ram_chip_t* r_chip, const ram_cell_t* r_cell){
    ram_cell_t* temp = NULL;
    if(ram_empty(r_chip)){
        copy_structs(&r_chip->arr[r_chip->quantity++], r_cell);
        return 0;
    }
    else{
        if(ram_full(r_chip)){
            if((temp = (ram_cell_t*) realloc(r_chip->arr, ++r_chip->chip_size * sizeof(ram_cell_t))) == NULL){
                return -1;
            }
            else{
                r_chip->arr = temp;
            }
        }
        copy_structs(&r_chip->arr[r_chip->quantity++], r_cell);
        return 0;
    }
}
ram_cell_t* ram_pop(ram_chip_t* chip){
    return NULL; //to do
}
void copy_structs(ram_cell_t* destination, const ram_cell_t* const source){
    destination->cell_id = source->cell_id;
    destination->value = source->value;
}