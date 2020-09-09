#ifndef syntax_h_
#define syntax_h_
#include <stdio.h>
#define COMMAND_ROW 26 

void print_help(const char*, size_t, const char*[], size_t, const char*[]);
extern const char* commands[COMMAND_ROW];
extern const char* ex_operands[COMMAND_ROW];

#endif