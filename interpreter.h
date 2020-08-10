#ifndef interpreter_h_
#define interpreter_h_
#include "stack.h"

typedef struct{ //data structure that holds flags states
  int flag0, flag1, flag2, flag4;
    unsigned short flag3;
}flags;


typedef struct{ //data structure that holds info about every single user input
char* data;
int type;
flags information;
}AnalyzedData;

void DEBUG_end(void);
void PrintString(char*);
char* UserInputToString(FILE* stream, unsigned* errno);
bool DataTypeAnalyzer(AnalyzedData*, char*);
void Interpreter(AnalyzedData*);
bool CheckCommand(char*, const char*, int);
//unsigned search_command(const char*, unsigned, unsigned);
#endif