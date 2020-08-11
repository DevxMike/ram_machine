#include "syntax.h"

const char* commands[COMMAND_ROW] = { //could be used as compare val to the input from file, so exemplary operands are in other array
    "ADD",
    "DIV",
    "HALT",
    "JGTZ",
    "JUMP",
    "JZERO",
    "LOAD",
    "MULT",
    "READ",
    "READ *",
    "START",
    "STORE",
    "STORE *",
    "SUB",
    "WRITE"
};
const char* ex_operands[COMMAND_ROW] = {
    "x //add x to R0 value",
    "x //divide R0 val by x",
    "<none> //end the algorithm",
    "<name_of_loop> //if R0 contains a positive integer jump to loop",
    "<name_of_loop> //jumps to <name_of_loop>",
    "<name_of_loop> //if R0 val equals to 0 jump to loop",
    "x //stores x in R0 (special register)",
    "x //multiply R0 val by x",
    "x //read from input to Rx",
    "x //get Rx val that equals y and read from input to Ry",
    "<none> //indicates start of algorithm",
    "x //copies value from R0 in Rx",
    "x //get value from Rx that equals to y and copy R0 val to Ry",
    "x //sub x from R0 value",
    "x //write Rx to output"
};


void print_help(const char* program_str, size_t rows_com, const char* com[], size_t rows_ex, const char* ex[]){
    printf(
        "This program needs an existing file to work properly.\n"
        "i.e. \"%s <file_name>\"\n\n"
        "Syntax:\n"
        "1 2 3 4 5 6 7 8 9 10 //integer input, not obligatory\n"
        "START - entry point\n"
        "<COMMANDS> <OPERANDS> - operations\n"
        "HALT - end of algorithm\n\n"
        "Available commands:\n",
        program_str
    );
    if(commands != NULL){ //debug
       for(const char** i = commands, **j = ex_operands; i < commands + rows_com, j < ex_operands + rows_ex; ++i, ++j){
           printf("%s %s\n", *i, *j);
       }
       printf("\n");
    }
}
