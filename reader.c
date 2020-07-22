#include "reader.h"
#include <ctype.h>

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