#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool has_invalid_chars(char* pt){
    char* temp = pt;
    while(*temp){ //while *temp is a non NULL char
        if(!isalpha(*temp++)){
            break;
        }
    }
    if(*temp != '\0'){ //if '\0' is not pointed val
        return true; //return true, because string contains forbidden chars
    }
    else{
        return false; //else return false
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

char** read_file(char* f_name, size_t* sizeof_arr){
    char** tasks = NULL;
    //change the body of this function
    //test cases
    tasks = (char**)malloc(sizeof(char*) * size);
    for(size_t i = 0; i < size; ++i){
        tasks[i] = (char*)malloc(sizeof(char) * strlen(temp[i]) + 1);
        strcpy(tasks[i], temp[i]);
    }
    *sizeof_arr = size;
    //end of test cases
    return tasks;
}