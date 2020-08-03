#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "reader.h"
#include "errors.h"
#include "syntax.h"

const char DEBUG_STRING[][70] = { //debug string array
    "CANNOT ANALYZE DATA",
    "int",
    "double",
    "single letter",
    "string of letters",
    "string of letters numbers and dots",
    "string of letters and numbers",
    "string of numbers and dots",
    "string of letters, '*' char and int (indirect addressing)",
    "COMMAND"
};

void Interpreter(AnalyzedData* data){ //interprets tasks
	if(data->type >= 0){ //if a rare bug has not occured
		printf("input = \"%s\" -> %s\n", data->data, DEBUG_STRING[data->type]); //print debug string
	}
	printf("DEBUG:DataTypeAnalyzer - type = %d | flag0 = %d | flag1 ", data->type ,data->information.flag0); //print flags states
	printf("= %d | flag2 = %d | flag3 = %d | flag4 \"command_id\" = %d\n", data->information.flag1, data->information.flag2, data->information.flag3, data->information.flag4);
}

bool DataTypeAnalyzer(AnalyzedData* data, char* str){
	int i = 0;
	int flag0 = 0; //if >= 1 str contains numbers
	int flag1 = 0; //if >= 1 str contains "." or ","
	int flag2 = 0; //if >= 1 str contains letters
	unsigned short flag3 = 0; //quantity of '*' chars (indirect addressing)
	int flag4 = 0; //command id number
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

	if(state == 4)
	  {
	    switch(flag2)
	      {
		
	      case 3:
		if(CheckCommand(str, commands[4], flag2))
		  {
		    state = 9;
		    flag4 = 5;
		  }
		if(CheckCommand(str, commands[5], flag2))
		  {
		    state = 9;
		    flag4 = 6;
		  }
		if(CheckCommand(str, commands[7], flag2))
		  {
		    state = 9;
		    flag4 = 8;
		  }
		break;
		
	      case 4:
		if(CheckCommand(str, commands[1], flag2))
		  {
		    state = 9;
		    flag4 = 2;
		  }
		if(CheckCommand(str, commands[6], flag2))
		  {
		    state = 9;
		    flag4 = 7;
		  }
		if(CheckCommand(str, commands[8], flag2))
		  {
		    state = 9;
		    flag4 = 9;
		  }
		if(CheckCommand(str, commands[11], flag2))
		  {
		    state = 9;
		    flag4 = 12;
		  }
		if(CheckCommand(str, commands[12], flag2))
		  {
		    state = 9;
		    flag4 = 13;
		  }
		if(CheckCommand(str, commands[14], flag2))
		  {
		    state = 9;
		    flag4 = 15;
		  }
		break;
		
	      case 5:
		if(CheckCommand(str, commands[0], flag2))
		  {
		    state = 9;
		    flag4 = 1;
		  }
		if(CheckCommand(str, commands[2], flag2))
		  {
		    state = 9;
		    flag4 = 3;
		  }
		if(CheckCommand(str, commands[10], flag2))
		  {
		    state = 9;
		    flag4 = 11;
		  }
		if(CheckCommand(str, commands[13], flag2))
		  {
		    state = 9;
		    flag4 = 14;
		  }
		break;
		
	      }
	  }
	
	data->type = state;
	
	data->information.flag0 = flag0; //copy flag info
	data->information.flag1 = flag1;
	data->information.flag2 = flag2;
	data->information.flag3 = flag3;
	data->information.flag4 = flag4;

	
	if(state >= 0 && state <= 9){ //if state is as expected
		data->data = str;
		return true;
	}
	else{
		data->data = NULL;
		return false;
	}	
}

char* UserInputToString(FILE* stream, unsigned* errno){ //get user input by scanning every single char from stdin and allocating just enough memory 
	char* uits, *uits_pt, *temp;
	char input;
	size_t i = 1;

	if((uits = (char*)malloc(i * sizeof(char))) == NULL){
		*errno = STRING_MEM_ALLOC_ERR;
		return NULL;
	}
	uits_pt = uits;
	while((input = peek(stream)) != EOF && (input != ';' && input != '\n')){
		*uits_pt = getc(stream);
		if((temp = realloc(uits, ++i)) == NULL){
			*errno = STRING_MEM_ALLOC_ERR;
			return NULL;
		}
		uits = temp;
		++uits_pt;
	}
	clear_stream(stream);
	*uits_pt = '\0';
	*errno = 0;
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
 
bool CheckCommand(char* str1, const char* str2, int sl)
{
  int j = 0;
  int i = 0;
  for(i=0 ; i<sl ; i++)
    {
      if(str1[i] == str2[i])
	j++;
    }
  
  if(i == j)
    return true;
  else
    return false;
}
