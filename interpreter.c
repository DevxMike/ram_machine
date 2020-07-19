#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char DEBUG_STRING[][50] = {
    "CANNOT ANALYZE DATA",
    "input = int",
    "input = double",
    "input = single letter",
    "input = string of letters",
    "input = string of letters numbers and dots",
    "input = string of letters and numbers",
    "input = string of numbers and dots"
};

void Interpreter(char* str){

}

AnalyzedData DataTypeAnalyzer(char* str){
	AnalyzedData data;
	int i = 0;
	int flag0 = 0; //if >= 1 str contains numbers
	int flag1 = 0; //if >= 1 str contains "." or ","
	int flag2 = 0; //if >= 1 str contains letters
	unsigned short flag3 = 0; //quantity of '*' chars (indirect addressing)
	int state = 0; //value depends on the flag states
	data.type = 0;
	data.data = NULL;
	char* pt = str;

	while(*pt){
		if((isalnum(*pt) && !isalpha(*pt)) && *pt != ';') ++flag0;
		if(*pt == '.' || *pt == ',') ++flag1;
		if(isalpha(*pt++)) ++flag2;
		++i;
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
		case 1:
		case 2:
		case 3:
		case 4:
		case 5: 
		case 6:
		case 7:
			printf("\n%s\n", DEBUG_STRING[state]);
			data.type = state;
			data.data = str;
		break;
		default:
			printf("\n a rare bug just happened, good luck will be upon you \n");
		break;
	}
	printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 = %d | flag2 = %d\n",state ,flag0, flag1, flag2);
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
		while(*str){
			printf("%c", *str++);
		}
}

void DEBUG_end(){
	printf("\nEnd Of DEBUG - input whatever to exit\n");
	getchar();
}


