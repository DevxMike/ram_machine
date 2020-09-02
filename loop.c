#include "loop.h"
#include <string.h>

void init_loop(loop_container_t** loop, unsigned* errno){

}
void add_loop_element(loop_container_t* loop, const loop_t* el, unsigned* errno){
    
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