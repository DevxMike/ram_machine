#ifndef loop_list_h
#define loop_list_h
#include "task_queue.h"

typedef task_queue_data_t list_data_t;

typedef struct list_element{
    list_data_t data;
    struct list_element* next;
}list_element_t;

void push_back(list_element_t**, const list_data_t*);
void free_list(list_element_t**);

#endif