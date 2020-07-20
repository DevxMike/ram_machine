#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "stack.h"

int main() 	//------------------------------------------------main S
{
    char* m_str;
    call_stack_t* call_stack = NULL;
    if((call_stack = init_stack(50)) != NULL){
        printf("stack initialized\n\n");
        print_stack_status(call_stack);
        AnalyzedData data0;
        m_str = UserInputToString();
        printf("\n\nYOUR INPUT: ");
        PrintString(m_str);
        printf("\n\nDATA TYPE:\n");
        if(DataTypeAnalyzer(&data0, m_str)){
            Interpreter(&data0);
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
        exit(0x01);
    }

    return 0;
}			//------------------------------------------------main E