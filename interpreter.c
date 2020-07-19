#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>

void Interpreter(char* str){

}

AnalyzedData DataTypeAnalyzer(char* str){
	AnalyzedData data;
	int i = 0;
	int flag0 = 0; //if >= 1 str contains numbers
	int flag1 = 0; //if >= 1 str contains "." or ","
	int flag2 = 0; //if >= 1 str contains letters
	int state = 0; //value depends on the flag states
	data.type = 0;
	data.data = NULL;

		while(str[i] != '\0')
		{
			if((str[i] > 48 && str[i] < 57) && str[i] != ';')
				flag0 = flag0 + 1;
			if(str[i] == '.' || str[i] == ',')
				flag1 = flag1 + 1;
			if((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123))
				flag2 = flag2 + 1;
			i = i + 1;
		}

		if(flag0 >= 1 && flag1 == 0 && flag2 == 0)
			state = 1; //integer
		if(flag0 >= 1 && flag1 == 1 && flag2 == 0)
			state = 2; //double
		if(flag0 == 0 && flag1 == 0 && flag2 == 1)
			state = 3; //single letter
		if(flag0 == 0 && flag1 == 0 && flag2 > 1)
			state = 4; //string of letters
		if(flag0 >= 1 && flag1 > 1 && flag2 >= 1)
			state = 5; //string of letters numbers and "." or ","
		if(flag0 >= 1 && flag1 == 0 && flag2 >= 1)
			state = 6; //string of letters and numbers
		if(flag0 >= 1 && flag1 > 1 && flag2 == 0)
			state = 7; //string of numbers and dots
		
		switch(state)
		{
			case 0:
				printf("\nCANNOT ANALYZE DATA\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
			break;
			case 1:
				printf("\ninput = int\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 1;
				data.data = str;
			break;
			case 2:
				printf("\ninput = double\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 2;
				data.data = str;
			break;
			case 3:
				printf("\ninput = single letter\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 3;
				data.data = str;
			break;
			case 4:
				printf("\ninput = string of letters\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 4;
				data.data = str;
			break;
			case 5:
				printf("\ninput = string of letters numbers and dots\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 5;
				data.data = str;
			break;
			case 6:
				printf("\ninput = string of letters and numbers\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 6;
				data.data = str;
			break;
			case 7:
				printf("\ninput = string of numbers and dots\n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
				data.type = 7;
				data.data = str;
			break;
			default:
				printf("\n a rare bug just happened, good luck will be upon you \n");
				printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
			break;
		}
		
	return data;	
}

char* UserInputToString(){
	char* uits;
	char input;
	int i = 0;

	uits = (char*)calloc(1, sizeof(char));

		do{
			input = getchar();
			if(input == '\n' || input == ';')
			{
				uits[i] = '\0';
				//printf("DEBUG:UserInputToString - input exeption 'newline' ';'\n");
			}
			else
			{
				uits[i] = input;
				i = i + 1;
				uits = (char*)realloc(uits, (i + 1) * sizeof(char));
				//printf("DEBUG:UserInputToString - input insertion\n");		
			}
			//printf("DEBUG:UserInputToString - input[%d] = %c\n", i, uits[i]);
		}while(input != '\n' && input != ';');
	return uits;
}

//-------------------------MISC-----------------------------------
//----------------------FUNCTIONS---------------------------------
void PrintString(char* str){
	int i = 0;

		while(str[i] != '\0')
		{
			printf("%c", str[i]);
			i = i + 1;
			//printf("DEBUG:PrintString - str[%d] = %c", i, str[i]);
		}
}

void DEBUG_end(){
	printf("\nEnd Of DEBUG - input whatever to exit\n");
	getchar();
}


