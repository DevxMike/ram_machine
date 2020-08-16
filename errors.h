#ifndef errors_h_
#define errors_h_

#include <stdlib.h>
#include <stdio.h>

void exit_w_code(unsigned exit_code); //exit with specified exit code

//exit code definitions
extern const unsigned STACK_INIT_ERR; //if stack init fails (bad alloc)
extern const unsigned TASK_QUEUE_INIT_ERR; //if task queue init fails (bad alloc)
extern const unsigned NO_FILE_NAME_ERR; //if user didnt call the program in the right way
                                        //ex: <program_name> <file_w_pseudo_assmebly> or <program_name> -h for help
extern const unsigned FILE_NAME_ERR; //string <file_name> contains forbidden chars
extern const unsigned WRONG_SYNTAX_ERR; //if analysis failed
extern const unsigned TASK_ARR_ALLOC_ERR; //if alloc for task arr failed
extern const unsigned NO_FILE_ERR; //if file doesnt exist
extern const unsigned EMPTY_FILE_ERR;
extern const unsigned STRING_MEM_ALLOC_ERR;
extern const unsigned INPUT_MEM_ALLOC_ERR;
extern const unsigned SYNTAX_ERR;
#endif