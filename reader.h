#ifndef reader_h_
#define reader_h_
#include <stdbool.h>
#include <string.h>
//test Grzegorza
//test
bool has_invalid_chars(char* pt); //checks if file_name has valid chars
char** read_file(char* f_name, size_t* sizeof_arr); //read task list from file
int peek(FILE* stream);
#endif