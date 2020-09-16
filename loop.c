#include "loop.h"
#include <string.h>
#include "loop_heap.h"

loop_container_t* init_loop(){
    loop_container_t* temp = NULL;

    if((temp = (loop_container_t*)malloc(sizeof(loop_container_t))) == NULL){
        return NULL;
    }
    else{ //if memory allocation for loops` container did not fail
        if((temp->arr = (loop_t*) malloc(sizeof(loop_t))) == NULL){
            return NULL;
        }
        else{ //and if memory allocation for an array of loops did not fail
            temp->quantity = 0;
            temp->max_size = 1;
            return temp;
        }
    }
}

int loop_full(const loop_container_t* container){
    return container->quantity == container->max_size;
}
int loop_empty(const loop_container_t* container){
    return container->quantity == 0;
}

void add_loop_element(loop_container_t* container, const loop_t* el){
    loop_t* temp = NULL;

    if(loop_full(container)){ //if container is full, realloc memory
        if((temp = (loop_t*)realloc(container->arr, ++container->max_size * sizeof(loop_t))) == NULL){
            exit_w_code(LOOP_PROCESSING_ERR); //if memory reallocation failed
        }
        else{
            container->arr = temp; 
        }
    }
    temp = &(container->arr[container->quantity++]); //and copy data
    strcpy(temp->loop_et, el->loop_et);
    copy_list(&temp->task_list, el->task_list);
}

const loop_t* search_loop(const loop_container_t* loop, const char* et, unsigned left, unsigned right){ //assuming structure is sorted by DESC
    if(left <= right){
        unsigned mid = (left + right)/2;
        if(!strcmp(et, loop->arr[mid].loop_et)){
            return &loop->arr[mid];
        }
        else if(strcmp(et, loop->arr[mid].loop_et) > 0){
            return search_loop(loop, et, left, mid - 1);
        }
        else{
            return search_loop(loop, et, mid + 1, right);
        }
        
    }
    return NULL;
}