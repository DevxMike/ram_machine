#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

const char DEBUG_STRING[][70] = { //debug string array
    "CANNOT ANALYZE DATA",
    "int",
    "double",
    "single letter",
    "string of letters",
    "string of letters numbers and dots",
    "string of letters and numbers",
    "string of numbers and dots",
	"string of letters, '*' char and int (indirect addressing)"
};

void Interpreter(const AnalyzedData* data){ //interprets tasks
	if(data->type >= 0){ //if a rare bug has not occured
		printf("input = \"%s\" -> %s\n", data->data, DEBUG_STRING[data->type]); //print debug string
	}
	printf("DEBUG:DataTypeAnalyzer - state = %d | flag0 = %d | flag1 ", data->type ,data->information.flag0); //print flags states
	printf("= %d | flag2 = %d | flag3 = %d\n", data->information.flag1, data->information.flag2, data->information.flag3);
}

bool DataTypeAnalyzer(AnalyzedData* data, char* str){
	int i = 0;
	int flag0 = 0; //if >= 1 str contains numbers
	int flag1 = 0; //if >= 1 str contains "." or ","
	int flag2 = 0; //if >= 1 str contains letters
	unsigned short flag3 = 0; //quantity of '*' chars (indirect addressing)
	int state = 0; //value depends on the flag states
	data->type = 0;
	data->data = NULL;
	char* pt = str;

	while(*pt){
		if((isalnum(*pt) && !isalpha(*pt)) && *pt != ';') ++flag0;
		if(*pt == '.' || *pt == ',') ++flag1;
		if(*pt == '*') ++flag3;
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
	if(flag0 >= 1 && flag1 == 0 && flag2 >= 1 && flag3 == 0)
		state = 6; //string of letters and numbers
	if(flag0 >= 1 && flag1 > 1 && flag2 == 0)
		state = 7; //string of numbers and dots
	if(flag0 >= 1 && flag1 == 0 && flag2 > 1 && flag3 == 1)
		state = 8; //contains letters, numbers and '*' char
	data->type = state;
	
	data->information.flag0 = flag0; //copy flag info
	data->information.flag1 = flag1;
	data->information.flag2 = flag2;
	data->information.flag3 = flag3;
	if(state >= 0 && state <= 8){ //if state is as expected
		data->data = str;
		return true;
	}
	else{
		data->data = NULL;
		return false;
	}	
}

char* UserInputToString(){ //get user input by scanning every single char from stdin and allocating just enough memory 
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
void PrintString(char* str){ //prints a string
	while(*str){
		printf("%c", *str++);
	}
}

void DEBUG_end(){
	printf("\nEnd Of DEBUG - input whatever to exit\n");
	getchar();
}


