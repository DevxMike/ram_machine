#ifndef syntax_h_
#define syntax_h_
#include <stdio.h>
#define COMMAND_ROW 15
#define COMMAND_COL 15  

void print_help(const char*, size_t, const char*[], size_t, const char*[]);
extern const char* commands[COMMAND_ROW];
extern const char* ex_operands[COMMAND_ROW];
extern void(*operation[COMMAND_ROW])(void); //to do

#endif