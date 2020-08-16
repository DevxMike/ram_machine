#include "stack.h"
#include <stdlib.h>
#include <string.h>


call_stack_t* init_stack(size_t size){
    call_stack_t* temp = NULL;
    if((temp = (call_stack_t*)malloc(sizeof(call_stack_t))) != NULL){ //if alloc didnt fail
        temp->max = size; //init the stact
        temp->quantity = 0;
        if((temp->data = (stack_data_t*) malloc(sizeof(stack_data_t) * size)) != NULL) //if alloc didnt fail
            return temp;
        else
            return NULL;
    }
    else{
        return NULL;
    }
}
void print_stack_status(call_stack_t* call_stack){ //prints general info about stack
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
bool s_push(call_stack_t* stack, const stack_data_t* data){ //pushes struct to the top of the stack
    stack_data_t* temp;
    if(call_stack_full(stack)){ //if stack is not full we can push an element
        return false;
    }
    else{
        temp = &stack->data[stack->quantity++]; 
        copy_data_struct(temp, data);
        return true;
    }
}
stack_data_t* s_pop(call_stack_t* stack){ //pops element down the stack
    stack_data_t* temp, *result;
    if(call_stack_empty(stack)){ //if stack is not empty element can be popped down
        return NULL;
    }
    else{
        temp = &stack->data[--stack->quantity];
        if((result = (stack_data_t*) malloc(sizeof(stack_data_t))) == NULL){ //if alloc failed
            return NULL;
        }
        else{
            copy_data_struct(result, temp); //else copy data to newly allocated memory
            return result;
        }
    }
}
bool call_stack_full(const call_stack_t* stack){ //returns bool val if stack is full
    return stack->max == stack->quantity;
}
bool call_stack_empty(const call_stack_t* stack){ //returns bool val if stack is empty
    return stack->quantity == 0;
}
void copy_data_struct(stack_data_t* destination, const stack_data_t* source){ //copies stack/queue data
    strcpy(destination->command, source->command);
    strcpy(destination->operand_st, source->operand_st);
    destination->cmd_id = source->cmd_id;
}