#ifndef reader_h_
#define reader_h_
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

//test Grzegorza
//test
bool has_invalid_chars(char* pt,  char* ex); //checks if file_name has valid chars
char** read_file(char* f_name, size_t* sizeof_arr, unsigned* errno); //read task list from file
int peek(FILE* stream);
#endif