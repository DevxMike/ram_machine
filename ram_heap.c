#include "ram_heap.h"
#include <stdlib.h>
#include "errors.h"

int ram_heap_empty(const ram_heap_t* ram_heap){
    return ram_heap->elements == 0; //if quantity equals to 0 then ram_heap is empty
}
int ram_heap_full(const ram_heap_t* ram_heap){
    return ram_heap->elements == ram_heap->ram_heap_size; //if quantity equals to ram_heap`s size then it is full
}
int greater(const id_type id1, const id_type id2){
    return id1 > id2; 
}
void ram_shift_up(ram_heap_t* ram_heap, size_t index){
    if(index > 0){
        if(greater(ram_heap->arr[index].cell_id, ram_heap->arr[(index - 1) / 2].cell_id)){ //check if newly added node is greater than it`s parrent
            swap_structs(&ram_heap->arr[index], &ram_heap->arr[(index - 1) / 2]); //if so, swap them
            ram_shift_up(ram_heap, (index - 1) / 2); //and call function to check if ram_heap`s order has been achieved
        }
    }
}
void ram_shift_down(ram_heap_t* ram_heap, size_t index, size_t left, size_t right){

    if(left < ram_heap->elements && right < ram_heap->elements){ //if left and right child exist
        if(greater(ram_heap->arr[left].cell_id, ram_heap->arr[right].cell_id)){ //if left child is greater than right one
            if(greater(ram_heap->arr[left].cell_id, ram_heap->arr[index].cell_id)){ //check if left child is greater than root going down the tree
                swap_structs(&ram_heap->arr[left], &ram_heap->arr[index]); //swap items
                ram_shift_down(ram_heap, left, 2*left + 1, 2*left + 2); //call function to restore order
            }
        }
        else{ //else if right one is greater
            if(greater(ram_heap->arr[right].cell_id, ram_heap->arr[index].cell_id)){ //if right is greater than root going down the tree
                swap_structs(&ram_heap->arr[right], &ram_heap->arr[index]);//swap items
                ram_shift_down(ram_heap, right, 2*right + 1, 2*right + 2);//call function to restore order
            }
        }
    }
    else if(left < ram_heap->elements){ //if there is no right child
        if(greater(ram_heap->arr[left].cell_id, ram_heap->arr[index].cell_id)){ //check if left child is greater than root going down the tree
            swap_structs(&ram_heap->arr[left], &ram_heap->arr[index]); //swap items
            ram_shift_down(ram_heap, left, 2*left + 1, 2*left + 2); //call function to restore order
        }
    }
    
}
int ram_heap_push(ram_heap_t* ram_heap, const ram_heap_data_t* data, unsigned* errno){
    ram_heap_data_t* temp = NULL;
    size_t i;

    if(ram_heap_empty(ram_heap)){
            copy_structs(&ram_heap->arr[ram_heap->elements++], data); //no need to sort if thats only one element in structure
            *errno = 0;
            return 0;
    }
    else{
        if(ram_heap_full(ram_heap)){
            if((temp = (ram_heap_data_t*)realloc(ram_heap->arr, sizeof(ram_heap_data_t) * ++ram_heap->ram_heap_size)) == NULL){
                *errno = HEAP_EL_ERR;
                return -1;
            }
            else{
                ram_heap->arr = temp;
            }
        }
    }
    i = ram_heap->elements;
    copy_structs(&ram_heap->arr[ram_heap->elements++], data);
    ram_shift_up(ram_heap, i);
    return 0;
}

void ram_heap_pop(ram_heap_t* ram_heap, ram_chip_t* ram){
    if(!ram_heap_empty(ram_heap)){
        ram_push(ram, &ram_heap->arr[0]);   //copy max value struct to destination named as source
        copy_structs(&ram_heap->arr[0], &ram_heap->arr[--ram_heap->elements]); //create last node to be a root, decrease elements quantity
        ram_shift_down(ram_heap, 0, 1, 2); //restore ram_heap`s order
    }
}
ram_heap_t* init_ram_heap(){
    ram_heap_t* temp = NULL; //temporary pointer 

    if((temp = (ram_heap_t*)malloc(sizeof(ram_heap_t))) != NULL){ //if memory allocation didn`t fail
        if((temp->arr = (ram_heap_data_t*)malloc(sizeof(ram_heap_data_t))) != NULL){
            temp->elements = 0;
            temp->ram_heap_size = 1;
        }
    }

    return temp;
}