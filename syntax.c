#include "syntax.h"

const char* commands[COMMAND_ROW] = { //could be used as compare val to the input from file, so exemplary operands are in other array
    "ADD",
    "ADD *",
    "ADD =",
    "DIV",
    "DIV *",
    "DIV =",
    "HALT",
    "JGTZ",
    "JUMP",
    "JZERO",
    "LOAD",
    "LOAD *",
    "LOAD =",
    "MULT",
    "MULT *",
    "MULT =",
    "READ",
    "READ *", 
    "STORE",
    "STORE *",
    "SUB",
    "SUB *",
    "SUB =",
    "WRITE",
    "WRITE *"
};
const char* ex_operands[COMMAND_ROW] = {
    "x //add Rx`s val to R0 value",
    "x //get y from Rx and add Ry`s val to R0 value",
    "x //add x val to R0 value",
    "x //div R0 val by Rx value",
    "x //get y from Rx and div R0 by Ry",
    "x //div R0 by x",
    "<none> //end the algorithm",
    "<name_of_loop> //if R0 contains a positive integer jump to loop",
    "<name_of_loop> //jumps to <name_of_loop>",
    "<name_of_loop> //if R0 val equals to 0 jump to loop",
    "x //stores Rx in R0",
    "x //get y from Rx and store Ry in R0",
    "x //stores x in R0",
    "x //multiply R0 val by Rx value",
    "x //get y from Rx and multiply R0 by Ry",
    "x //multiply R0 by x",
    "x //read from input to Rx",
    "x //get y from Rx and read from input to Ry",
    "x //copies R0 value into Rx",
    "x //get y from Rx and store R0`s val in Ry",
    "x //substract Rx`s val from R0 value",
    "x //get y from Rx and substract Ry`s val from R0 value",
    "x //substract x val from R0 value",
    "x //write Rx to output",
    "x //get y from Rx and write Ry to output"
};


void print_help(const char* program_str, size_t rows_com, const char* com[], size_t rows_ex, const char* ex[]){
    printf( //print help and available commands
        "This program needs an existing file to work properly.\n"
        "i.e. \"%s <file_name>\"\n\n"
        "Syntax:\n"
        "1 2 3 4 5 6 7 8 9 10 //integer input, not obligatory\n"
        "label:; optional"
        "<COMMANDS> <OPERANDS> - operations\n"
        "HALT - end of algorithm\n\n"
        "loops:\n\n"
        "comments in code:\n"
        "example: \"ADD =5; add 5 to R0`s value\"\n\n"
        "Available commands:\n",
        program_str
    );
    if(commands != NULL){ //print commands
       for(const char** i = commands, **j = ex_operands; i < commands + rows_com, j < ex_operands + rows_ex; ++i, ++j){
           printf("%s %s\n", *i, *j);
       }
       printf("\n");
    }
}