#ifndef errors_h_
#define errors_h_
#include <stdlib.h>
#include <stdio.h>

const char ERROR_DESC[][70] = { //error descriptions
    "Failed to allocate memory for call stack.",
    "Failed to allocate memory for task queue.",
    "No file name passed to the program.",
    "Wrong file name, use letters only.",
    "Wrong syntax. <program_name> -h for help."
};

void exit_w_code(unsigned exit_code){ //function that prints exit code
    printf("EXIT CODE: 0x%08x\n", exit_code);
    if(exit_code){ //in case an error occured it suggests to check docs
        printf("%s\n", ERROR_DESC[exit_code - 1]);
    }
    exit(exit_code); //exit with exit code
}



//exit code definitions
const unsigned STACK_INIT_ERR = 0x01; //if stack init fails (bad alloc)
const unsigned TASK_QUEUE_INIT_ERR = 0x02; //if task queue init fails (bad alloc)
const unsigned NO_FILE_NAME_ERR = 0x03; //if user didnt call the program in the right way
                                        //ex: <program_name> <file_w_pseudo_assmebly> or <program_name> -h for help
const unsigned BAD_FILE_NAME_ERR = 0x04; //string <file_name> contains forbidden chars
const unsigned WRONG_SYNTAX_ERR = 0x05; //if analysis failed
#endif