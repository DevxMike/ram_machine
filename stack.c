#include "stack.h"
#include <stdlib.h>
#include <string.h>

call_stack_t* init_stack(size_t size){
    call_stack_t* temp = NULL;
    if((temp = (call_stack_t*)malloc(sizeof(call_stack_t))) != NULL){
        temp->max = size;
        temp->quantity = 0;
        if((temp->data = (stack_data_t*) malloc(sizeof(stack_data_t) * size)) != NULL)
            return temp;
    }
    else{
        return NULL;
    }
}
void print_stack_status(call_stack_t* call_stack){
    printf("call_stack address: %p\nmax_size: %zu\nactual quantity: %zu\n", (void*)call_stack, call_stack->max, call_stack->quantity);
    printf("data address: %p\n", (void*)call_stack->data);
    if(call_stack_empty(call_stack)){
        printf("stack is empty\n\n");
    }
    else if(call_stack_full(call_stack)){
        printf("stack is full\n\n");
    }
    else{
        printf("stack is not empty\n\n");
    }
}
bool push(call_stack_t* stack, const stack_data_t* data){
    stack_data_t* temp;
    if(call_stack_full(stack)){
        return false;
    }
    else{
        temp = &stack->data[stack->quantity++];
        copy_data_struct(temp, data);
        return true;
    }
}
stack_data_t* pop(call_stack_t* stack){
    stack_data_t* temp, *result;
    if(call_stack_empty(stack)){
        return NULL;
    }
    else{
        temp = &stack->data[--stack->quantity];
        if((result = (stack_data_t*) malloc(sizeof(stack_data_t))) == NULL){
            return NULL;
        }
        else{
            copy_data_struct(result, temp);
            return result;
        }
    }
}
bool call_stack_full(const call_stack_t* stack){
    return stack->max == stack->quantity;
}
bool call_stack_empty(const call_stack_t* stack){
    return stack->quantity == 0;
}
void copy_data_struct(stack_data_t* destination, const stack_data_t* source){
    strcpy(destination->command, source->command);
    strcpy(destination->operand_st, source->operand_st);
    strcpy(destination->operand_nd, source->operand_nd);
}