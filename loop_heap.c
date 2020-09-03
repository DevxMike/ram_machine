#include "loop_heap.h"
#include "errors.h"
#include <stdlib.h>

loop_heap_t* init_loop_heap(){
    loop_heap_t* temp = NULL;
    if((temp = (loop_heap_t*)malloc(sizeof(loop_heap_t))) != NULL){
        temp->size = temp->quantity = 0;
        if((temp->arr = (loop_t*)malloc(sizeof(loop_t))) == NULL){
            return NULL;
        }
    }
    return temp;
}
void swap_strings(char* str1, char* str2, unsigned n){
    if(n > 0){
        char c = *str1;
        *str1++ = *str2;
        *str2++ = c;
        swap_strings(str1, str2, n - 1);
    }
}
void swap_loops(loop_t* l1, loop_t* l2){
    list_element_t* tmp_list = NULL;
    
    swap_strings(l1->loop_et, l2->loop_et, OP_SIZE);
    tmp_list = l1->task_list;
    l1->task_list = l2->task_list;
    l2->task_list = tmp_list;
}
void loop_heap_push(loop_heap_t* heap, const loop_t* el){
    if(loop_heap_empty(heap)){

    }
}
void shift_down(loop_heap_t* heap, unsigned index, unsigned left, unsigned right){

}
loop_t* loop_heap_pop(loop_heap_t* heap){
    loop_t* tmp = NULL;
    if(!loop_heap_empty(heap)){
        if((tmp = (loop_t*)malloc(sizeof(loop_t))) == NULL){
            return NULL;
        }
        else{
            copy_list(&tmp->task_list, heap->arr[0].task_list);
            strcpy(tmp->loop_et, heap->arr[0].loop_et);
            copy_list(&heap->arr[0].task_list, heap->arr[--heap->quantity].task_list);
            shift_down(heap, 0, 1, 2);
        }
    }
    return tmp;
}
int loop_heap_empty(const loop_heap_t* heap){
    return heap->quantity == 0;
}
int loop_heap_full(const loop_heap_t* heap){
    return heap->quantity == heap->size;
}