#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "task_queue.h"
#include <string.h>
#include "reader.h"
#include <stdbool.h>
#include "errors.h"
#include "syntax.h"
#include "ram.h"
#include "ram_heap.h"

#ifndef main_h_
#define main_h_

typedef struct{
    unsigned EXIT_CODE;
    task_queue_t* queue;
    AnalyzedData data;
    input_data_t input;
    tasks_t task_arr;
    ram_heap_t* ram_heap;
    ram_chip_t* ram_chip;
}main_vars_t;
void init_main(main_vars_t*);


#endif