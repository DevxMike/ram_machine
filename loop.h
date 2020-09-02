#ifndef loop_h
#define loop_h
#include "loop_list.h"
#include "errors.h"

typedef struct{
    char* loop_et;
    list_element_t* task_list;
}loop_t;

typedef struct{
    size_t quantity;
    loop_t* arr;
}loop_container_t;

extern char** loops;

void init_loop(loop_container_t**, unsigned*);
void add_loop_element(loop_container_t*, const loop_t*, unsigned*);
const loop_t* search_loop(const loop_container_t*, const char*, unsigned, unsigned);

#endif