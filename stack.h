#ifndef stack_h_
#define stack_h_
#include <stdio.h>
#include <stdbool.h>

//git test

typedef struct { //struct used to hold commands and operands
    char command[5];
    char operand_st[11];
}stack_data_t;

typedef struct{ //struct used to hold pointer to stack elements and general info about stack
    size_t max;
    size_t quantity;
    stack_data_t* data;    
}call_stack_t;

bool s_push(call_stack_t* stack, const stack_data_t* data);
void print_stack_status(call_stack_t* call_stack);
stack_data_t* s_pop(call_stack_t* stack);
bool call_stack_full(const call_stack_t* stack);
bool call_stack_empty(const call_stack_t* stack);
void copy_data_struct(stack_data_t* destination, const stack_data_t* source);
call_stack_t* init_stack(size_t size);
#endif