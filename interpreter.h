#ifndef interpreter_h_
#define interpreter_h_

typedef struct
{
char* data;
int type;
}AnalyzedData;


void DEBUG_end(void);
void PrintString(char*);
char* UserInputToString(void);
AnalyzedData DataTypeAnalyzer(char*);
void Interpreter(char*);
#endif
