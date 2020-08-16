#ifndef ram_h
#define ram_h

#include <stdio.h>
typedef struct{
    unsigned long long cell_id; //creating i.e. 3 "ram cells" is much better than not using 10000 ram cells  
    int value; //value to be hold
}ram_cell_t;

typedef struct{
    size_t quantity; //quantity of ram cells used in user`s algorithm
    ram_cell_t* arr; //array of "ram cells"
}ram_chip_t;



#endif