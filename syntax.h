#ifndef syntax_h_
#define syntax_h_
#include <stdio.h>
#define COMMAND_ROW 3
#define COMMAND_COL 15  

void print_help(const char*, size_t rows, size_t cols, char commands[rows][cols]);
extern char commands[COMMAND_ROW][COMMAND_COL];

#endif