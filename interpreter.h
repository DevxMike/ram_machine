#ifndef interpreter_h_
#define interpreter_h_
#include "stack.h"
#include "task_queue.h"
#include <stdbool.h>
#include "ram.h"
#include "ram_heap.h"
#include "main.h"

typedef struct{ //data structure that holds flags states
  int flag0, flag1, flag2, flag4;
    unsigned short flag3;
}flags;


typedef struct{ //data structure that holds info about every single user input
char* data;
int type;
flags information;
}AnalyzedData;

extern bool has_loops;
void PrintString(char*);
char* UserInputToString(FILE*, unsigned*);
bool DataTypeAnalyzer(AnalyzedData*, char*);
int Interpreter(AnalyzedData*, task_queue_t*, unsigned*, size_t);
bool CheckCommand(char*, const char*, int);
int search_command(const char*, int, int);
int* input_data(char*, unsigned*, size_t*);
int split_string(AnalyzedData*, task_queue_data_t*);
void to_upper_case(char*);
int tasker(ram_chip_t*, task_queue_data_t*, ram_heap_t*, ram_heap_t*, input_data_t*);
int string_to_int(char*);
id_type string_to_id_type(char*);
#endif