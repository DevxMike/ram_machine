#ifndef stack_h_
#define stack_h_
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char command[5];
    char operand_st[11];
    char operand_nd[11]; 
}stack_data_t;

typedef struct{
    size_t max;
    size_t quantity;
    stack_data_t* data;    
}call_stack_t;

bool push(call_stack_t* stack, const stack_data_t* data);
stack_data_t* pop(call_stack_t* stack);
bool call_stack_full(const call_stack_t* stack);
bool call_stack_empty(const call_stack_t* stack);
void copy_data_struct(stack_data_t* destination, const stack_data_t* source);
#endif