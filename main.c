#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int main() 	//------------------------------------------------main S
{
    char* m_str;
    AnalyzedData data0;
        
        
        m_str = UserInputToString();
        printf("\n\nYOUR INPUT: ");
        PrintString(m_str);
        printf("\n\nDATA TYPE:\n");
        data0 = DataTypeAnalyzer(m_str);
        printf("\n\nEND\n");

    DEBUG_end();
    return 0;
}			//------------------------------------------------main E