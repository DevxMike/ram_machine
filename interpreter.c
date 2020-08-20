#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "reader.h"
#include "errors.h"
#include "syntax.h"
#include <string.h>

bool has_loops = false; //if algo has loops, interpreter changes its value to true

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

int ADD(ram_chip_t* chip, id_type cell_id){

}
int DIV(ram_chip_t* chip, id_type cell_id){

}
int LOAD(ram_chip_t* chip, int val){

}
int MULT(ram_chip_t* chip, id_type cell_id){

}
int READ(ram_chip_t* chip, id_type cell_id, addressing adr){

}
int STORE(ram_chip_t* chip, id_type cell_id, addressing adr){

}
int SUB(ram_chip_t* chip, id_type cell_id){

}
int WRITE(ram_chip_t* chip, id_type cell_id){
	
}

int to_number(char number){ //converts char into a number
	return number - '0';
}

int tasker(ram_chip_t* ram, task_queue_data_t* data){
	switch(data->cmd_id){
		case 0: //ADD operation
		printf("ADD\n");
		break;
		
		case 1: //DIV operation
		break; 
		
		case 3: //JGTZ operation
		case 4: //JUMP operation
		case 5: //JZERO operation
		break;

		case 6: //LOAD operation
		break;
		
		case 7: //MULT operation
		break;
		
		case 8: //READ operation
		case 9:	//READ * operation
		break;

		case 11: //STORE operation
		case 12: //STORE * operation
		break;

		case 13: //SUB operation
		break;
		
		case 14: //write operation
		break;
	}
}


int Interpreter(AnalyzedData* data, task_queue_t* queue, unsigned* status, size_t line){ //interprets tasks
	task_queue_data_t temp;
	int* arr = NULL;

	if(split_string(data, &temp) == 2){
		return 1;
	}
	else{
		if(temp.cmd_id != -1){
			q_push(queue, &temp);
			*status = 0;
			return 0;
		}
		else{
			printf("line %ld: %s - not a command.\n", line + 1, temp.command);
			*status = WRONG_SYNTAX_ERR;
			return -1;
		}
	}
}

int is_num(char number){ //determines if char is a number
	return (isalnum(number) && !isalpha(number));
}

bool DataTypeAnalyzer(AnalyzedData* data, char* str){
	int i = 0;
	int flag0 = 0; //if >= 1 str contains numbers
	int flag1 = 0; //if >= 1 str contains "." or ","
	int flag2 = 0; //if >= 1 str contains letters
	unsigned short flag3 = 0; //quantity of '*' chars (indirect addressing)
	int flag4 = 0; //if == 1 contains ':', it`s a label of a loop
	int state = 0; //value depends on the flag states
	data->type = 0;
	data->data = NULL;
	char* pt = str;

	while(*pt){ //check string to analyze it
		if((is_num(*pt)) && *pt != ';') ++flag0;
		if(*pt == '.') ++flag1;
		if(isalpha(*pt)) ++flag2;
		if(*pt == '*') ++flag3;
		if(*pt++ == ':') ++flag4;
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
	if(flag0 == 0 && flag1 == 0 && flag2 >= 1 && flag3 == 0 && flag4 == 1)
		state = 9; //contains letter/letters and ':' char

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

	if((uits = (char*)malloc(sizeof(char))) == NULL){ //if alloc for string failed
		*errno = STRING_MEM_ALLOC_ERR;
		return NULL;
	}
	uits_pt = uits;
	while((input = peek(stream)) != EOF && (input != ';' && input != '\n')){ //while char in stream is not a ';' or newline char
		*uits_pt = getc(stream); //get char from stream and copy into memory on heap
		if((temp = realloc(uits, ++i * sizeof(char))) == NULL){ //if realloc failed
			*errno = STRING_MEM_ALLOC_ERR;
			return NULL;
		}
		uits = temp;
		++uits_pt;
	}
	//clear_stream(stream); //clear stream from chars 
	*uits_pt = '\0'; //end the string with '\0' char
	*errno = 0;
	return uits;
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

int string_to_int(char* str, int n){
	return 0; //to do
}

int* input_data(char* string, unsigned* errno, size_t* size){
	int* temp_tab = NULL, *tab_pt = NULL, temp_int = 0;
	char* str_pt = string;
	bool minus = false;
	size_t len = 1;

	if(*string == '\0'){ //if string is empty
		return NULL;
	}
	if((temp_tab = (int*)malloc(len*sizeof(int))) == NULL){ //if memory alloc failed
		*errno = INPUT_MEM_ALLOC_ERR;
		return NULL;
	}
	*temp_tab = 0;
	for(char* pt = string; *pt != '\0'; ++pt){
		if(*pt == '-'){
			minus = true;
			continue;
		}
		if(isspace(*pt)){
			if(minus){
				temp_tab[len - 1] *= -1;
				minus = false;
			}
			if((tab_pt = (int*)realloc(temp_tab, ++len * sizeof(int))) == NULL){ //if memory realloc failed
			*errno = INPUT_MEM_ALLOC_ERR;
			return NULL;
			}else{
				temp_tab = tab_pt;
				temp_tab[len - 1] = 0;
			}
		}
		if(is_num(*pt)){
			temp_tab[len - 1] *= 10;
			temp_tab[len - 1] += to_number(*pt);
		}
	}
	*size = len;
	*errno = 0;
	return temp_tab;
}
int search_command(const char* cmd, int left, int right){ //binary search, seeks for a string passed as a parameter
	int middle = (left + right) / 2;
	if(left > right || left < 0){
		return -1;
	}
	if(strcmp(cmd, commands[middle]) == 0){
		return middle;
	}
	else if(strcmp(cmd, commands[middle]) < 0){
		return search_command(cmd, left, middle - 1);
	}
	else if(strcmp(cmd, commands[middle]) > 0){
		return search_command(cmd, middle + 1, right);
	}
}
void cut_string(char* string, task_queue_data_t* temp_src, bool has_op){ //slices string into two parts
	char* str_pt = string;
	char* src_pt = temp_src->command;
	size_t ctrl = 0;

	while(isalpha(*str_pt) && ctrl++ < CMD_SIZE - 1){
		*src_pt++ = *str_pt++; //while command, copy to the memory where commands are hold
	}
	ctrl = 0;
	*src_pt = '\0'; //end string with '\0' char
	to_upper_case(temp_src->command); //transform string to upper case 
	if(has_op){ //if has operand (command is neither a loop nor START nor HALT command)
		src_pt = temp_src->operand_st;  
		while(*str_pt && ctrl++ < OP_SIZE - 1){ //while *str_pt is not a '\0' char
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
		case 1:
		return 2; //string of integers
		break;

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
	if((index = search_command(temp_src->command, 0, COMMAND_ROW)) >= 0){ //check if command exists
		index = data->type == 8? index + 1 : index;
		strcpy(temp_src->command, commands[index]); //copy the right command from syntax.c file (either direct or indirect addressing) 
	}
	else{
		return temp_src->cmd_id = index;
	}
	temp_src->cmd_id = index;
	return has_operand? 1 : 0;
}