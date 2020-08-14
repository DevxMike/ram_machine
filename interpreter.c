#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "reader.h"
#include "errors.h"
#include "syntax.h"
#include <string.h>

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
	task_queue_data_t temp;

	split_string(data, &temp);
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

	while(*pt){ //check string to analyze it
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
	
	data->type = state; //set type of input 
	
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

	if((uits = (char*)malloc(i * sizeof(char))) == NULL){ //if alloc for string failed
		*errno = STRING_MEM_ALLOC_ERR;
		return NULL;
	}
	uits_pt = uits;
	while((input = peek(stream)) != EOF && (input != ';' && input != '\n')){ //while char in stream is not a ';' or newline char
		*uits_pt = getc(stream); //get char from stream and copy into memory on heap
		if((temp = realloc(uits, ++i)) == NULL){ //if realloc failed
			*errno = STRING_MEM_ALLOC_ERR;
			return NULL;
		}
		uits = temp;
		++uits_pt;
	}
	clear_stream(stream); //clear stream from chars 
	*uits_pt = '\0'; //end the string with '\0' char
	*errno = 0;
	return uits;
}

int is_num(char number){ //determines if char is a number
	return (isalnum(number) && !isalpha(number));
}
int to_number(char number){ //converts char into a number
	return number - '0';
}
void to_upper_case(char* string){ //converts string into upper case 
	if(*string)
		do{
			if(!isalpha(*string)){
				continue;
			}
			*string = toupper(*string);
	}while(++string, *string);
}
int* input_data(char* string, unsigned* errno, size_t* size){
	int* temp_tab = NULL, *tab_pt = NULL, temp_int = 0;
	char* str_pt = string;
	size_t len = 0;

	if(*string == '\0'){ //if string is empty
		return NULL;
	}
	if((temp_tab = (int*)malloc(1*sizeof(int))) == NULL){ //if memory alloc failed
		*errno = INPUT_MEM_ALLOC_ERR;
		return NULL;
	}
	do{
		if((tab_pt = (int*)realloc(temp_tab, ++len * sizeof(int))) == NULL){ //if memory realloc failed
			*errno = INPUT_MEM_ALLOC_ERR;
			return NULL;
		}
		temp_tab = tab_pt; //if realloc didn`t fail
		while(is_num(*str_pt) && *str_pt != '\0'){ //while part of a string is an integer
			temp_int += to_number(*str_pt++); //simple conversion from string to int
			if(is_num(*str_pt)){
				temp_int *= 10;
			}
		}
		temp_tab[len - 1] = temp_int;
		temp_int = 0;
	}while((++str_pt, *str_pt != '\0'));

	*size = len;
	*errno = 0;

	return temp_tab;
}
void PrintString(char* str){ //prints a string
	while(*str){
		printf("%c", *str++);
	}
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

int search_command(const char* cmd, int left, int right, int middle){ //binary search, seeks for a string passed as a parameter
	if(strcmp(cmd, commands[middle]) == 0){
		return middle;
	}
	else if(strcmp(cmd, commands[middle]) < 0){
		return search_command(cmd, left, middle, (left + middle)/2);
	}
	else if(strcmp(cmd, commands[middle]) > 0){
		return search_command(cmd, middle, right, (right + middle)/2);
	}
	else{
		return -1; 
	}
}
void cut_string(char* string, task_queue_data_t* temp_src, bool has_op){ //slices string into two parts
	char* str_pt = string;
	char* src_pt = temp_src->command;

	while(isalpha(*str_pt)){
		*src_pt++ = *str_pt++; //while command, copy to the memory where commands are hold
	}
	*src_pt = '\0'; //end string with '\0' char
	to_upper_case(temp_src->command); //transform string to upper case 
	if(has_op){ //if has operand (command is neither a loop nor START nor HALT command)
		src_pt = temp_src->operand_st;  
		while(*str_pt){ //while *str_pt is not a '\0' char
			if(is_num(*str_pt)){ 
				(*src_pt++ = *str_pt++);
			} 
			else{ 
				(++str_pt);
			} 
		}
		*src_pt = '\0';//end string with '\0' char
	}
}
int split_string(AnalyzedData* data, task_queue_data_t* temp_src){ //splits string "ADD* 5" into two strings <cmd>"ADD" <operand>"5";
	char delim[2];
	int index;
	bool has_operand = true;

	switch(data->type){ 
		case 4: //START, HALT, some kind of loop etc
		has_operand = false;
		break;

		case 6: //ADD 5, DIV 2 etc
		*delim = ' ';
		break;

		case 8: //indirect addressing
		*delim = '*';
		break;
		
		default: //syntax error
		return -1;
	}
	
	cut_string(data->data, temp_src, has_operand); //slice string

	if((index = search_command(temp_src->command, 0, COMMAND_ROW, COMMAND_ROW/2)) >= 0){ //check if command exists
		strcpy(temp_src->command, commands[*delim == '*'? ++index : index]); //copy the right command from syntax.c file (either direct or indirect addressing) 
	}
	else{
		return -1;
	}
	printf("\ncommand: %s, typeof data: %d, delim: \"%c\", index of command: %d\n", temp_src->command, data->type, *delim, index); //print debug info

	return has_operand? 1 : 0;
}