#include "ram.h"
#include <stdlib.h>

int ram_empty(ram_chip_t* chip){ //check if ram is empty
    return chip->quantity == 0;
}
int ram_full(ram_chip_t* chip){ //check if ram is full
    return chip->quantity == chip->chip_size;
}

void swap_structs(ram_cell_t* r1, ram_cell_t* r2){ //swap data in structs
    ram_cell_t temp;

    copy_structs(&temp, r1);
    copy_structs(r1, r2);
    copy_structs(r2, &temp);
}

int ram_search(const id_type target, const ram_chip_t* chip, int left, int right){
    if(left <= right){ //search ram cell index in the array by it`s id (binary search)
        int mid = ((right + left) / 2);
        return(
            chip->arr[mid].cell_id == target? mid : (
                chip->arr[mid].cell_id > target? ram_search(target, chip, mid + 1, right) : ram_search(target, chip, left, mid - 1)
            )
        );
    }
    return -1;
}

ram_chip_t* init_ram(){
    ram_chip_t* temp = NULL;
    
    if((temp = (ram_chip_t*) malloc(sizeof(ram_chip_t))) != NULL){ //if alloc didn`t fail
        if((temp->arr = (ram_cell_t*)malloc(sizeof(ram_cell_t))) == NULL){ 
            return NULL;
        }
        temp->chip_size = 1; //set basic data in struct
        temp->quantity = 0;
    }

    return temp;
}
int ram_push(ram_chip_t* r_chip, const ram_cell_t* r_cell){
    ram_cell_t* temp = NULL;
    if(ram_empty(r_chip)){ //if ram is empty
        copy_structs(&r_chip->arr[r_chip->quantity++], r_cell); //place data at 0 index
        return 0;
    }
    else{
        if(ram_full(r_chip)){ //else there is a possibility, that there is not enough memory for next ram cell
            if((temp = (ram_cell_t*) realloc(r_chip->arr, ++r_chip->chip_size * sizeof(ram_cell_t))) == NULL){
                return -1;
            }
            else{ //if realloc didn`t fail
                r_chip->arr = temp;
            }
        }
        copy_structs(&r_chip->arr[r_chip->quantity++], r_cell); //copy data 
        return 0;
    }
}
void copy_structs(ram_cell_t* destination, const ram_cell_t* const source){ //copy src struct into dst 
    destination->cell_id = source->cell_id;
    destination->value = source->value;
}