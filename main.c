#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "stack.h"
#include "errors.h"

int main(int argc, char** argv){
    unsigned EXIT_CODE = 0;

    char* m_str;
    call_stack_t* call_stack = NULL;
    AnalyzedData data;
    if((call_stack = init_stack(50)) != NULL){
        printf("stack initialized\n\n");
        print_stack_status(call_stack);
        m_str = UserInputToString();
        printf("\n\nYOUR INPUT: ");
        PrintString(m_str);
        printf("\n\nDATA TYPE:\n");
        if(DataTypeAnalyzer(&data, m_str)){
            Interpreter(&data);
        }
        else{
            printf("rare bug has just occured, good luck with that!\n");
        }
        DEBUG_end();
        free(call_stack->data);
        free(call_stack);
    }
    else{
        printf("failed to initialize call stack!\n");
        EXIT_CODE = STACK_INIT_ERR;
    }

    printf("exit code: 0x%04x\n", EXIT_CODE);
    if(EXIT_CODE > 0){
        printf("Check documentation/readme for error numbers description.\n");
    }
    return EXIT_CODE;
}