#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "reader.h"
#include "errors.h"
#include "syntax.h"
#include <string.h>
#include "main.h"

bool has_loops = false; //if algo has loops, interpreter changes its value to true
bool start_occured = false;

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

typedef enum{
	read = 0, store,  write 
}other_type; //other operations types

typedef enum {
	add = 0, sub, mult, divide, load //arithmetic operations types
}arithmetic_type;

int other_ops(ram_chip_t* chip, int index, input_data_t* data, other_type op_type){ //perform other type of operations
	int zero_index;
	switch(op_type){
		case read:
		if(data->element < data->arr_size){
			chip->arr[index].value = data->data_arr[data->element++]; //store integer from input in ram cell
			return 1; 
		}
		else{
			printf("INPUT EMPTY\n");
		}
		break;
		case store:
		if((zero_index = ram_search(0, chip, 0, chip->quantity - 1)) < 0){
			return -2; //could not find R0 index
		}	
		else{
			chip->arr[index].value = chip->arr[zero_index].value; //copy R0 value to desired ram cell
		}
		break;
		case write:
		printf("R%llu value: %d\n", chip->arr[index].cell_id, chip->arr[index].value); //print Rx value
		break;
	}
	return 1;
}

int arithmetic_ops(ram_chip_t* chip, int val, arithmetic_type t){ //perform arithmetic operations
	int zero_index = ram_search(0, chip, 0, chip->quantity - 1);
	if(zero_index < 0){
		return -1;
	}
	else{
		switch(t){
			case add:
			chip->arr[zero_index].value += val; //add value to R0
			break;
			case sub:
			chip->arr[zero_index].value -= val; //substract value from R0
			break;
			case mult:
			chip->arr[zero_index].value *= val; //multiply R0 by value
			break;
			case divide:
			chip->arr[zero_index].value /= val; //divide R0 by value
			break;
			case load:
			chip->arr[zero_index].value = val; //load value into R0
			break;
		}	
		return 1;
	}
}
int other_ops_type(int cmd){ //return other operations type
	switch(cmd){
		case 8: case 9:
		return read;
		break;
		case 11: case 12:
		return store;
		break;
		case 14:
		return write;
		break;
	}
}
int is_indirect_add(int cmd){
	switch(cmd){
		case 9: case 12:
		return true;
		break;
		default:
		return false;
		break;
	}
}
int arithmetic_ops_type(int cmd){ //return arithmetic operation type
	switch(cmd){
		case 0:
		return add;
		break;
		case 1:
		return divide;
		break;
		case 6:
		return load;
		break;
		case 7:
		return mult;
		break;
		case 13:
		return sub;
		break;
		default:
		return -1;
		break;
	}
}
int to_number(char number){ //converts char into a number
	return number - '0';
}
bool is_id_cmd_type(int x){ //if command requires register address return true
	switch(x){
		case 8: case 9: case 11: case 12: case 14:
		return true;
		break;
		default:
		return false;
		break;
	}
}
int tasker(ram_chip_t* ram, task_queue_data_t* data, ram_heap_t* heap, input_data_t* input){
	id_type ram_id;
	ram_heap_data_t temp;
	unsigned errno = 0;
	int index = 0;

	if(is_id_cmd_type(data->cmd_id)){ //check if command either requires integer or ram cell address
		ram_id = string_to_id_type(data->operand_st); //convert string to unsigned long long
		if((index = ram_search(ram_id, ram, 0, ram->quantity - 1)) < 0){ //search for struct with certain ram_id
			temp.cell_id = ram_id;
			temp.value = 0;
			ram_heap_push(heap, &temp, &errno);  //if not found, add a new one
			if(errno){
				exit_w_code(errno);
			}
			ram_heap_sort(heap, ram); //if successful, sort to be able to perform binary search
		}
		if(is_indirect_add(data->cmd_id)){ //if indirect addressing
			if(ram->arr[index].value >= 0){ //check if value in register is positive
				ram_id = (id_type)ram->arr[index].value;
				if((index = ram_search(ram_id, ram, 0, ram->quantity - 1)) < 0){ //then search for it in ram chip
				temp.cell_id = ram_id;
				temp.value = 0;
				ram_heap_push(heap, &temp, &errno); //if not found, add a ram cell
				if(errno){
					exit_w_code(errno);
				}
				ram_heap_sort(heap, ram); //if successful, sort
				}
			}
			else{
				printf("Value in register R%llu is not positive!\n", ram_id);
				return -1;
			}
		}
	}
	switch(data->cmd_id){
		case 0: case 13: case 1: case 6: case 7:
		arithmetic_ops(ram, string_to_int(data->operand_st), arithmetic_ops_type(data->cmd_id));
		break;
		
		case 3: //JGTZ operation
		case 4: //JUMP operation
		case 5: //JZERO operation
		break;
		
		case 8: case 9:	case 11: case 12: case 14:
		if((index = ram_search(ram_id, ram, 0, ram->quantity - 1)) < 0){
			return -1;
		}
		other_ops(ram, index, input, other_ops_type(data->cmd_id));
		break;
	}
}


int Interpreter(AnalyzedData* data, task_queue_t* queue, unsigned* status, size_t line){ //interprets tasks
	task_queue_data_t temp;
	int* arr = NULL;

	if(split_string(data, &temp) == 2){
		return 1;
	}
	if(temp.cmd_id == 10){
		start_occured = true;
	}
	if(start_occured){
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
	int flag5 = 0; //if == 1 contains '=' char
	int state = 0; //value depends on the flag states
	data->type = 0;
	data->data = NULL;
	char* pt = str;

	while(*pt){ //check string to analyze it
		if((is_num(*pt)) && *pt != ';') ++flag0;
		if(*pt == '.') ++flag1;
		if(isalpha(*pt)) ++flag2;
		if(*pt == '*') ++flag3;
		if(*pt == ':') ++flag4;
		if(*pt++ == '=') ++flag5;
		++i;
	}

	if(flag0 >= 1 && flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag5 == 0)
		state = 1; //integer
	if(flag0 >= 1 && flag1 == 1 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag5 == 0)
		state = 2; //double
	if(flag0 == 0 && flag1 == 0 && flag2 == 1 && flag3 == 0 && flag4 == 0 && flag5 == 0)
		state = 3; //single letter
	if(flag0 == 0 && flag1 == 0 && flag2 > 1 && flag3 == 0 && flag4 == 0 && flag5 == 0)
	        state = 4; //string of letters
	if(flag0 >= 1 && flag1 > 1 && flag2 >= 1 && flag3 == 0 && flag4 == 0 && flag5 == 0)
		state = 5; //string of letters numbers and "." or ","
	if(flag0 >= 1 && flag1 == 0 && flag2 >= 1 && flag3 == 0 && flag4 == 0 && flag5 == 0)
		state = 6; //string of letters and numbers
	if(flag0 >= 1 && flag1 > 1 && flag2 == 0 && flag4 == 0 && flag5 == 0)
		state = 7; //string of numbers and dots
	if(flag0 >= 1 && flag1 == 0 && flag2 > 1 && flag3 == 1 && flag4 == 0 && flag5 == 0)
		state = 8; //contains letters, numbers and '*' char
	if(flag0 == 0 && flag1 == 0 && flag2 >= 1 && flag3 == 0 && flag4 == 1 && flag5 == 0)
		state = 9; //contains letter/letters and ':' char
	if(flag0 >= 1 && flag1 == 0 && flag2 >= 1 && flag3 == 0 && flag4 == 0 && flag5 == 1)
		state = 10;
	data->type = state; //set type of input 
	
	data->information.flag0 = flag0; //copy flag info
	data->information.flag1 = flag1;
	data->information.flag2 = flag2;
	data->information.flag3 = flag3;
	data->information.flag4 = flag4;
	data->information.flag5 = flag5;
	
	if(state >= 0 && state <= 10){ //if state is as expected
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
int transform_to_int(char* str, int initial){ //both operations assume that input is correct (string contains a number)
	if(*str){
		initial *= 10;
		initial += to_number(*str);
		transform_to_int(++str, initial);
	}
	else{
		return initial;
	}
}
id_type transform_to_id_type(char* str, id_type initial){ //both operations assume that input is correct (string contains a number)
	if(*str){
		initial *= 10;
		initial += to_number(*str);
		transform_to_id_type(++str, initial);
	}
	else{
		return initial;
	}
}
int string_to_int(char* str){
	if(is_num(*str)){
		return transform_to_int(str, 0);
	}
	else if(*str == '-'){
		return transform_to_int(++str, 0) * -1;
	}
}
id_type string_to_id_type(char* str){
	while(*str && !is_num(*str)){
		++str;
		continue;
	}
	return transform_to_id_type(str, 0);
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
	int middle = left + (right - left) / 2;
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
	if((index = search_command(temp_src->command, 0, COMMAND_ROW - 1)) >= 0){ //check if command exists
		index = data->type == 8? index + 1 : index;
		strcpy(temp_src->command, commands[index]); //copy the right command from syntax.c file (either direct or indirect addressing) 
	}
	else{
		return temp_src->cmd_id = index;
	}
	temp_src->cmd_id = index;
	printf("%s\n", temp_src->command);
	return has_operand? 1 : 0;
}