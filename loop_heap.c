#include "loop_heap.h"
#include "errors.h"
#include <stdlib.h>

loop_heap_t* init_loop_heap(){
    loop_heap_t* temp = NULL;
    if((temp = (loop_heap_t*)malloc(sizeof(loop_heap_t))) != NULL){
        temp->size = temp->quantity = 0;
        temp->arr = NULL;
    }
    return temp;
}
void loop_heap_push(loop_heap_t* heap, const loop_t* el){

}
void loop_heap_pop(loop_heap_t* heap, loop_container_t* container){

}
int loop_heap_empty(const loop_heap_t* heap){
    return heap->quantity == 0;
}
int loop_heap_full(const loop_heap_t* heap){
    return heap->quantity == heap->size;
}