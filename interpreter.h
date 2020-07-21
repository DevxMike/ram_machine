#ifndef interpreter_h_
#define interpreter_h_
#include "stack.h"

typedef struct{
    int flag0, flag1, flag2;
    unsigned short flag3;
}flags;


typedef struct{
char* data;
int type;
flags information;
}AnalyzedData;

void DEBUG_end(void);
void PrintString(char*);
char* UserInputToString(void);
bool DataTypeAnalyzer(AnalyzedData*, char*);
void Interpreter(const AnalyzedData*);
void task_exec(stack_data_t*, int*);
#endif
