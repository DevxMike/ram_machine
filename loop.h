#ifndef loop_h
#define loop_h
#include "loop_list.h"
#include "errors.h"
#include "task_queue.h"

typedef struct{
    char loop_et[OP_SIZE];
    list_element_t* task_list;
}loop_t;

typedef struct{
    loop_t* arr;
    size_t quantity;
    size_t max_size;
}loop_container_t;

loop_container_t* init_loop(void);
void add_loop_element(loop_container_t*, const loop_t*);
const loop_t* search_loop(const loop_container_t*, const char*, unsigned, unsigned);
int loop_full(const loop_container_t*);
int loop_empty(const loop_container_t*);

#endif