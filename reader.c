#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"


void clear_stream(FILE* stream){
    char c;
    while((c = getc(stream)) && c != '\n'){
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
        if(!isalpha(*temp++)){
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

//for tests
const size_t size = 9;
const char temp[][30] = {
        "1",
        "1.5",
        "2,25",
        "c",
        "string",
        "string 2.5, 4.5",
        "string 22",
        "2..2,2314",
        "LOAD *5"
};

char** read_file(char* f_name, size_t* sizeof_arr, unsigned* errno){
    char** tasks = NULL;
    FILE* file_in = NULL;

    if((tasks = (char**)malloc(sizeof(char*))) == NULL){
        *errno = TASK_ARR_ALLOC_ERR;
        return NULL;
    }
    if((file_in = fopen(f_name, "rt")) == NULL){
        *errno = NO_FILE_ERR;
        return NULL;
    }
    if(peek(file_in) == EOF){
        *errno = EMPTY_FILE_ERR;
        fclose(file_in);
        free(tasks);
        return NULL;
    }
    //change the body of this function
    //test cases
    /*
    tasks = (char**)malloc(sizeof(char*) * size);
    for(size_t i = 0; i < size; ++i){
        tasks[i] = (char*)malloc(sizeof(char) * strlen(temp[i]) + 1);
        strcpy(tasks[i], temp[i]);
    }
    *sizeof_arr = size;
    */
    //end of test cases
    return NULL;
}