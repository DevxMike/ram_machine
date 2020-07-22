#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "stack.h"
#include "errors.h"
#include "task_queue.h"
#include <string.h>
#include "reader.h"
#include <stdbool.h>

int main(int argc, char** argv){
    unsigned EXIT_CODE = 0;
    char* m_str;
    call_stack_t* call_stack = NULL;
    task_queue_t* task_queue = NULL;
    AnalyzedData data;

    if(argc == 1){ //if argv contains program name only
        printf("Wrong usage. Try %s <file_name> or %s -h for help\n", argv[0], argv[0]);
        exit_w_code(NO_FILE_NAME_ERR);
    }
    else{
        if(strcmp(argv[1], "-h") == 0){ //if argv contains program name and "-h" string 
            printf("Some help message\n");
            exit_w_code(EXIT_CODE);
        } 
        else if(has_invalid_chars(argv[1])){ //if <file_name> string has forbidden chars
            exit_w_code(BAD_FILE_NAME_ERR);
        }
        EXIT_CODE = (call_stack = init_stack(50)) == NULL? STACK_INIT_ERR : 0; //init call stack
        if(EXIT_CODE){ //if call stack init fails
            exit_w_code(EXIT_CODE);
        }    
        EXIT_CODE = (task_queue = task_queue_init(50)) == NULL? TASK_QUEUE_INIT_ERR : 0; //init task queue
        if(EXIT_CODE){ //if task queue init fails
            exit_w_code(EXIT_CODE);
        }
        //print general info
        printf("stack initialized\n\n");
        print_stack_status(call_stack); 
        printf("task queue initialized\n\n");
        print_queue_status(task_queue);
        printf("file to be read: %s\n\n", argv[1]);
        m_str = UserInputToString(); //get input string from user
        printf("\n\nYOUR INPUT: ");
        PrintString(m_str);
        printf("\n\nDATA TYPE:\n");
        if(DataTypeAnalyzer(&data, m_str)){ //analyze data
            Interpreter(&data); //print debug info
        }
        else{
            printf("rare bug has just occured, good luck with that!\n");
        }
        DEBUG_end();
        free(call_stack->data);//free memory
        free(call_stack);

        exit_w_code(EXIT_CODE);  
    }    
}