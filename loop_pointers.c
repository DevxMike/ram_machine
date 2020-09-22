#include "loop_pointers.h"
#include <string.h>

pointers_container_t* init_pointers(void){
    pointers_container_t* temp = NULL;
    if(
        ((temp = (pointers_container_t*)malloc(sizeof(pointers_container_t))) == NULL) ||
        ((temp->arr = (loop_pointer_t**)malloc(sizeof(loop_pointer_t*))) == NULL) ||
        ((temp->arr[0] = (loop_pointer_t*)malloc(sizeof(loop_pointer_t))) == NULL)
    ){
        exit_w_code(LOOP_PROCESSING_ERR);
    }//if memory allocation didn`t fail
    temp->max = 1; //set basic struct fields
    temp->quantity = 0;

    return temp;
}
int pointers_full(const pointers_container_t* container){
    return container->max == container->quantity;
}
int pointers_empty(const pointers_container_t* container){
    return container->quantity == 0;
}
void add_pointer(pointers_container_t* container, loop_t* label, task_queue_element_t* next){
    loop_pointer_t** temp;

    if(pointers_full(container)){ //if container is full, there is need to realloc memory
        if(
            ((temp = (loop_pointer_t**)realloc(container->arr, sizeof(loop_pointer_t*) * (++container->max))) == NULL) ||
            ((temp[container->max - 1] = (loop_pointer_t*)malloc(sizeof(loop_pointer_t))) == NULL)
        ){
            exit_w_code(LOOP_PROCESSING_ERR);
        } //if realloc didnt fail
        container->arr = temp; 
    }
    container->arr[container->quantity]->pointer = label; //init pointer values
    container->arr[container->quantity++]->next_cmd = next;
}
loop_pointer_t* search_pointer(pointers_container_t* container, 
    const char* label, unsigned left, unsigned right){

    unsigned mid = (left + right) / 2;
    int cmp;

    if(left <= right){ //search pointer to loop (bin search)
        cmp = strcmp(label, container->arr[mid]->pointer->loop_et);
        return(
            cmp == 0? container->arr[mid] : (
                cmp > 0? search_pointer(container, label, left, mid - 1) : search_pointer(container, label, mid + 1, right)
            )
        );
    }
    return NULL;
}
loop_pointer_t* get_pointer(pointers_container_t* container, char* label){
    return search_pointer(container, label, 0, container->quantity - 1);
}

//heap ops

int cmp_pointers(const loop_pointer_t* p1, const loop_pointer_t* p2){
    return strcmp(p1->pointer->loop_et, p2->pointer->loop_et);
}   
void push_pointer_heap(pointers_container_t* heap, loop_pointer_t* pt){
    //to do
}
loop_pointer_t* pop_pointer_heap(pointers_container_t* heap){
    //to do
    return NULL;
}
void sort_pointers(pointers_container_t* container, pointers_container_t* heap){

}