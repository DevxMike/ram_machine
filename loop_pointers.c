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
void swap_data(loop_pointer_t** p1, loop_pointer_t** p2){
    loop_pointer_t* temp = *p1; //swap pointers to data (much faster than swapping the data)
    *p1 = *p2;
    *p2 = temp;   
}
int cmp_pointers(const loop_pointer_t* p1, const loop_pointer_t* p2){ //compare pointers by labels
    return strcmp(p1->pointer->loop_et, p2->pointer->loop_et);
}   
void pt_shift_up(pointers_container_t* heap, unsigned index){ //helpful with bringing back the order in tree right after inserting new element
    if(index > 0){
        unsigned temp = (index-1)/2;
        if(cmp_pointers(heap->arr[index], heap->arr[temp]) > 0){
            swap_data(&heap->arr[index], &heap->arr[temp]); //if new element is bigger than the old one in tree, swap their pointers
            pt_shift_up(heap, temp); //and continue the check
        }
    }
}
void push_pointer_heap(pointers_container_t* heap, loop_t* label, task_queue_element_t* next){
    add_pointer(heap, label, next); //add new element
    pt_shift_up(heap, heap->quantity - 1); //bring the order back in tree
}
void pt_shift_down(pointers_container_t* heap, unsigned index, unsigned left, unsigned right){
    if(left < heap->quantity && right < heap->quantity){
        unsigned greater = (
            cmp_pointers(heap->arr[left], heap->arr[right]) > 0? left : right
        );
        if(cmp_pointers(heap->arr[greater], heap->arr[index]) > 0){
            swap_data(&heap->arr[greater], &heap->arr[index]);
            pt_shift_down(heap, greater, 2*greater + 1, 2*greater + 2);
        }
    }
    else if(left < heap->quantity){
        if(cmp_pointers(heap->arr[left], heap->arr[index]) > 0){
            swap_data(&heap->arr[left], &heap->arr[index]);
            pt_shift_down(heap, left, 2*left + 1, 2*left + 2);
        }
    }
}
loop_pointer_t pop_pointer_heap(pointers_container_t* heap){
    loop_pointer_t temp;
    if(!pointers_empty(heap)){ //if heap is not empty
        temp.pointer = heap->arr[0]->pointer; //return value will be the first element in tree
        temp.next_cmd = heap->arr[0]->next_cmd;
        heap->arr[0]->pointer = heap->arr[--heap->quantity]->pointer; //replace the first with the last one
        heap->arr[0]->next_cmd = heap->arr[heap->quantity]->next_cmd;
        heap->arr[heap->quantity]->pointer = NULL;
        heap->arr[heap->quantity]->next_cmd = NULL; 
        pt_shift_down(heap, 0, 1, 2); //bring the order back in the tree
    }
    return temp;
}
void fill_heap(pointers_container_t* container, pointers_container_t* heap, unsigned n){
    if(n > 0){
        push_pointer_heap(heap, container->arr[n - 1]->pointer, container->arr[n - 1]->next_cmd);
        fill_heap(container, heap, n - 1);
    }
}
void sort_pointers(pointers_container_t* container, pointers_container_t* heap){
    loop_pointer_t temp;

    fill_heap(container, heap, container->quantity); // fill heap
    container->quantity = 0;

    while(!pointers_empty(heap)){ //while heap is not empty
        temp = pop_pointer_heap(heap); //pop a struct containing pointers
        add_pointer(container, temp.pointer, temp.next_cmd); //add pointers to sorted array
    }
}