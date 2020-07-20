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
        data0 = DataTypeAnalyzer(m_str);
        printf("\n\nEND\n");

        DEBUG_end();
    }
    else{
        printf("failed to initialize call stack!\n");
        exit(0x01);
    }

    return 0;
}			//------------------------------------------------main E