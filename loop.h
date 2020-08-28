#ifndef loop_h
#define loop_h
#include "loop_list.h"

typedef struct{
    char* loop_et;
    list_element_t* task_list;
}loop_element_t;

typedef struct{
    size_t quantity;
    loop_element_t* arr;
}loop_t;

extern char** loops;

#endif