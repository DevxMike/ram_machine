#include "stack.h"
#include <stdlib.h>
#include <string.h>

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