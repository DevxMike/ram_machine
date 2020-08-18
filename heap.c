#include "heap.h"
#include <stdlib.h>
#include "errors.h"

int heap_empty(const heap_t* heap){
    return heap->elements == 0;
}
int heap_full(const heap_t* heap){
    return heap->elements == heap->heap_size;
}

inline int greater(const id_type id1, const id_type id2){
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