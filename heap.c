#include "heap.h"
#include <stdlib.h>
#include "errors.h"

inline void copy_structs(heap_data_t* destination, heap_data_t* source){
    destination->cell_id = source->cell_id;
    destination->value = source->value;
}

void swap_structs(heap_data_t* r1, heap_data_t* r2){
    heap_data_t temp;

    copy_structs(&temp, r1);
    copy_structs(r1, r2);
    copy_structs(r2, &temp);
}

inline int greater(const id_t id1, const id_t id2){
    return id1 > id2;
}

void h_push(heap_t* heap, const heap_data_t* data, unsigned* errno){
    heap_data_t* temp = NULL;

    if(heap_empty(heap)){
            copy_structs(&heap->arr[heap->elements++], data); //no need to sort if thats only one element in structure
            *errno = 0;
    }
    else{
        if(heap_full(heap)){
            if((temp = (heap_data_t*)realloc(heap->arr, sizeof(heap_data_t) * ++heap->heap_size)) == NULL){
                *errno = HEAP_EL_ERR;
            }
            else{
                *errno = 0;
            }
        }
        copy_structs(&heap->arr[heap->elements++], data);
        //to do 
    }
}
heap_data_t* h_pop(heap_t* heap){
    //to do
    return NULL;
}
heap_t* init_heap(){
    heap_t* temp = NULL; //temporary pointer 

    if((temp = (heap_t*)malloc(sizeof(heap_t))) != NULL){ //if memory allocation didn`t fail
        if((temp->arr = (heap_data_t*)malloc(sizeof(heap_data_t))) != NULL){
            temp->elements = 0;
            temp->heap_size = 1;
        }
    }

    return temp;
}