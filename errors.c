#include "errors.h"
const char ERROR_DESC[][70] = { //error descriptions
    "Failed to allocate memory for call stack.",
    "Failed to allocate memory for task queue.",
    "No file name passed to the program.",
    "Wrong file name. Try <file_name>.txt.",
    "Wrong syntax. <program_name> -h for help.",
    "Mem alloc for tasks array failed.",
    "Such file doesn`t exist.",
    "File is empty.",
    "Mem alloc for string in stream failed.",
    "Mem alloc for input data failed.",
    "Could not allocate/reallocate memory for element.",
    "Could not init heap.",
    "Could not init ram.",
    "Could not process loop."
};

void exit_w_code(unsigned exit_code){ //function that prints exit code
    printf("\nEXIT CODE: 0x%08x\n", exit_code);
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
const unsigned FILE_NAME_ERR = 0x04; //string <file_name> contains forbidden chars
const unsigned WRONG_SYNTAX_ERR = 0x05; //if analysis failed
const unsigned TASK_ARR_ALLOC_ERR = 0x06; //if alloc for task arr failed
const unsigned NO_FILE_ERR = 0x07; //if file doesnt exist
const unsigned EMPTY_FILE_ERR = 0x08; //if file is empty
const unsigned STRING_MEM_ALLOC_ERR = 0x09; //if alloc for string failed
const unsigned INPUT_MEM_ALLOC_ERR = 0x0A; //if alloc for input integers failed
const unsigned HEAP_EL_ERR = 0x0B; //if memory allocation of reallocation in heap failed
const unsigned HEAP_INIT_ERR = 0x0C; //if heap init failed
const unsigned RAM_INIT_ERR = 0x0D; //if ram init failed
const unsigned LOOP_PROCESSING_ERR = 0x0E; //if failed to add to the list
