#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "interpreter.h"

void clear_stream(FILE* stream){
    char c;
    while((c = getc(stream)) != EOF && c != '\n'){
        continue;
    }
}

int peek(FILE* stream){ //check what char is next in the stream
    char c = getc(stream); //get char from stream
    ungetc(c, stream); //pass char back to stream
    return c; //return char
}

bool has_invalid_chars(char* pt, char* ex){
    char* temp = pt;
    char* ex_pt;
    while(*temp){ //while *temp is a non NULL char
        if(!isalnum(*temp++)){
            break;
        }
    }
    if(*(temp - 1) == '.'){ //if '\0' is not pointed val and '.' is a previous val
        ex_pt = ex;
        while(*temp && *ex_pt && (*temp++ == *ex_pt++)){ //check if the rest of f_name string matches file extension
            continue; //while chars match
        }
        if(*ex_pt != '\0' || *temp != '\0'){ 
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return true; //else return false
    }
}

char** read_file(char* f_name, size_t* sizeof_arr, unsigned* errno){
    char** tasks = NULL, **temp, *str;
    FILE* file_in = NULL;
    size_t lines = 1;
    
    if((file_in = fopen(f_name, "r")) == NULL){ //if failed to open the file (it does not exist)
        *errno = NO_FILE_ERR;
        return NULL;
    }
    if(peek(file_in) == EOF){ //if file is empty
        *errno = EMPTY_FILE_ERR;
        fclose(file_in);
        free(tasks);
        return NULL;
    }
    if((tasks = (char**)malloc(sizeof(char*))) == NULL){ //if could not alloc data for string array
        *errno = TASK_ARR_ALLOC_ERR;
        return NULL;
    }

    while(peek(file_in) != EOF){
        while(!isalnum(peek(file_in))){ //clear stream
            getc(file_in);
            continue;
        }
        str = UserInputToString(file_in, errno); //get string from file
        if((tasks[lines - 1] = (char*)malloc(sizeof(char) * (strlen(str) + 1))) == NULL){ //if memory alloc failed
            *errno = TASK_ARR_ALLOC_ERR;
            return NULL;
        }
        strcpy(tasks[lines - 1], str); //copy input from file to array of strings
        if((temp = realloc(tasks, ++lines * sizeof(char*))) == NULL){ //if realloc failed
            *errno = TASK_ARR_ALLOC_ERR;
            return NULL;
        }
        tasks = temp;
    }
    fclose(file_in); //close file
    *errno = 0;
    *sizeof_arr = --lines;
    return tasks; //return pointer to 2D arr of strings 
}