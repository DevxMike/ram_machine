#include "syntax.h"

char commands[COMMAND_ROW][COMMAND_COL] = {
    "command1",
    "command2",
    "command3"
};

void print_help(const char* program_str, size_t rows, size_t cols, char commands[rows][cols]){
    printf(
        "This program needs an existing file to work properly.\n"
        "i.e. \"%s <file_name>\"\n\n"
        "Syntax:\n"
        "START\n"
        "<COMMANDS> <OPERANDS>\n"
        "HALT\n\n"
        "Available commands:\n",
        program_str
    );
    if(commands != NULL){ //debug
       for(char (* i)[cols] = commands; i < commands + rows; ++i){
           printf("%s\n", *i);
       }
    }
}
