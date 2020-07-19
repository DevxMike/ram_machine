#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int main() 	//------------------------------------------------main S
{
char* m_str;
AnalyzedData data0;
	
	
	m_str = UserInputToString();
	printf("\n0\n");
	PrintString(m_str);
	printf("\n1\n");
	data0 = DataTypeAnalyzer(m_str);
	printf("\n2\n");

DEBUG_end();
return 0;
}			//------------------------------------------------main E