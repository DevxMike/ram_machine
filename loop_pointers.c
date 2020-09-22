#include "loop_pointers.h"
#include <string.h>

int cmp_pointers(const loop_pointer_t* p1, const loop_pointer_t* p2){
    return strcmp((*p1->pointer)->loop_et, (*p2->pointer)->loop_et);
}   
void push_pointer_heap(pointers_container_t* heap, loop_pointer_t* pt){
    
}
loop_pointer_t* pop_pointer_heap(pointers_container_t* heap){
    return NULL;
}
pointers_container_t* init_pointers(void){
    pointers_container_t* temp = NULL;
    if(
        ((temp = (pointers_container_t*)malloc(sizeof(pointers_container_t))) == NULL) ||
        ((temp->arr = (loop_pointer_t*)malloc(sizeof(loop_pointer_t))) == NULL) ||
        ((temp->arr[0].pointer = (loop_t**)malloc(sizeof(loop_t*))) == NULL)
    ){
        exit_w_code(LOOP_PROCESSING_ERR);
    }
    temp->max = 1;
    temp->quantity = 0;
    (*temp->arr[0].pointer)->task_list = NULL;

    return temp;
}