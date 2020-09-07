#include "loop.h"
#include <string.h>

void init_loop(loop_container_t** loop, unsigned* errno){

}
void add_loop_element(loop_container_t* loop, const loop_t* el){
    
}
void loop_sort(loop_container_t* container, loop_heap_t* heap){
    loop_t* temp = NULL;
    while(!loop_heap_empty(heap)){
        temp = loop_heap_pop(heap);
        if(temp == NULL){
            exit_w_code(LOOP_PROCESSING_ERR);
        }
        else{
            add_loop_element(container, temp);
        }
    }
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