#include "loop_heap.h"
#include "errors.h"
#include <stdlib.h>

loop_heap_t* init_loop_heap(){
    loop_heap_t* temp = NULL;
    if((temp = (loop_heap_t*)malloc(sizeof(loop_heap_t))) != NULL){ //if allocation didnt fail
        temp->quantity = 0; 
        if((temp->arr = (loop_t*)malloc(sizeof(loop_t))) == NULL){ //if allocation for loop data didnt fail
            return NULL;
        }
        temp->size = 1;
    }
    return temp;
}
void swap_strings(char* str1, char* str2, unsigned n){ //swaps two strings
    if(n > 0){
        char c = *str1;
        *str1++ = *str2;
        *str2++ = c;
        swap_strings(str1, str2, n - 1); //continue while n is not equal to 0
    }
}

int compare_loop(const loop_t* l1, const loop_t* l2){
    return strcmp(l1->loop_et, l2->loop_et);
}

void swap_loops(loop_t* l1, loop_t* l2){ //swaps two loops 
    list_element_t* tmp_list = NULL;
    
    swap_strings(l1->loop_et, l2->loop_et, OP_SIZE); //swap strings 
    tmp_list = l1->task_list; //swap pointers to task lists
    l1->task_list = l2->task_list;
    l2->task_list = tmp_list;
}
void loop_heap_push(loop_heap_t* heap, const loop_t* el){
    if(loop_heap_empty(heap)){
        //to do
    }
}

void shift_down(loop_heap_t* heap, unsigned index, unsigned left, unsigned right){
    if(left < heap->quantity && right < heap->quantity){ //if parent has two children nodes
        unsigned greater;
        if(compare_loop(&heap->arr[left], &heap->arr[right]) > 0){ //find greater child
            greater = left;
        }
        else{
            greater = right;
        }
        if(compare_loop(&heap->arr[greater], &heap->arr[index]) > 0){ //compare parent to greater child
            swap_loops(&heap->arr[greater], &heap->arr[index]); //if condition is met, swap loop data
            shift_down(heap, greater, 2*greater + 1, 2*greater + 2);//continue
        }
    }
    else if(left < heap->quantity){ //if parent has no right child 
        if(compare_loop(&heap->arr[left], &heap->arr[index]) > 0){ //check whether parent is smaller than it`s child
            swap_loops(&heap->arr[left], &heap->arr[index]); //swap data
            shift_down(heap, left, 2*left + 1, 2*left + 2); //continue
        }
    }
}
loop_t* loop_heap_pop(loop_heap_t* heap){
    loop_t* tmp = NULL;
    if(!loop_heap_empty(heap)){
        if((tmp = (loop_t*)malloc(sizeof(loop_t))) == NULL){ 
            return NULL;
        }
        else{ //if memory allocation didn`t fail
            copy_list(&tmp->task_list, heap->arr[0].task_list); //copy data to newly allocated memory
            strcpy(tmp->loop_et, heap->arr[0].loop_et);
            copy_list(&heap->arr[0].task_list, heap->arr[--heap->quantity].task_list); //last element as new root
            strcpy(heap->arr[0].loop_et, heap->arr[heap->quantity].loop_et);
            shift_down(heap, 0, 1, 2); //bring the order in the tree
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