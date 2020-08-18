#include "heap.h"
#include <stdlib.h>
#include "errors.h"

int heap_empty(const heap_t* heap){
    return heap->elements == 0; //if quantity equals to 0 then heap is empty
}
int heap_full(const heap_t* heap){
    return heap->elements == heap->heap_size; //if quantity equals to heap`s size then it is full
}
int greater(const id_type id1, const id_type id2){
    return id1 > id2; 
}
void shift_up(heap_t* heap, size_t index){
    if(index > 0){
        if(greater(heap->arr[index].cell_id, heap->arr[(index - 1) / 2].cell_id)){ //check if newly added node is greater than it`s parrent
            swap_structs(&heap->arr[index], &heap->arr[(index - 1) / 2]); //if so, swap them
            shift_up(heap, (index - 1) / 2); //and call function to check if heap`s order has been achieved
        }
    }
}
void shift_down(heap_t* heap, size_t index, size_t left, size_t right){

    if(left < heap->elements && right < heap->elements){ //if left and right child exist
        if(greater(heap->arr[left].cell_id, heap->arr[right].cell_id)){ //if left child is greater than right one
            if(greater(heap->arr[left].cell_id, heap->arr[index].cell_id)){ //check if left child is greater than root going down the tree
                swap_structs(&heap->arr[left], &heap->arr[index]); //swap items
                shift_down(heap, left, 2*left + 1, 2*left + 2); //call function to restore order
            }
        }
        else{ //else if right one is greater
            if(greater(heap->arr[right].cell_id, heap->arr[index].cell_id)){ //if right is greater than root going down the tree
                swap_structs(&heap->arr[right], &heap->arr[index]);//swap items
                shift_down(heap, right, 2*right + 1, 2*right + 2);//call function to restore order
            }
        }
    }
    else if(left < heap->elements){ //if there is no right child
        if(greater(heap->arr[left].cell_id, heap->arr[index].cell_id)){ //check if left child is greater than root going down the tree
            swap_structs(&heap->arr[left], &heap->arr[index]); //swap items
            shift_down(heap, left, 2*left + 1, 2*left + 2); //call function to restore order
        }
    }
    
}
int h_push(heap_t* heap, const heap_data_t* data, unsigned* errno){
    heap_data_t* temp = NULL;
    size_t i;

    if(heap_empty(heap)){
            copy_structs(&heap->arr[heap->elements++], data); //no need to sort if thats only one element in structure
            *errno = 0;
            return 0;
    }
    else{
        if(heap_full(heap)){
            if((temp = (heap_data_t*)realloc(heap->arr, sizeof(heap_data_t) * ++heap->heap_size)) == NULL){
                *errno = HEAP_EL_ERR;
                return -1;
            }
            else{
                heap->arr = temp;
            }
        }
    }
    i = heap->elements;
    copy_structs(&heap->arr[heap->elements++], data);
    shift_up(heap, i);
    return 0;
}
void h_pop(heap_t* heap, ram_chip_t* ram){
    if(!heap_empty(heap)){
        ram_push(ram, &heap->arr[0]);   //copy max value struct to destination named as source
        copy_structs(&heap->arr[0], &heap->arr[--heap->elements]); //create last node to be a root, decrease elements quantity
        shift_down(heap, 0, 1, 2); //restore heap`s order
    }
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