#ifndef errors_h_
#define errors_h_
#include <stdlib.h>
#include <stdio.h>

void exit_w_code(unsigned exit_code){
    printf("EXIT CODE: 0x%08x\n", exit_code);
    if(exit_code){
        printf("Check documentation/readme for error numbers description.\n");
    }
    exit(exit_code);
}

const unsigned STACK_INIT_ERR = 0x01;
const unsigned TASK_QUEUE_INIT_ERR = 0x02;
const unsigned NO_FILE_NAME_ERR = 0x03;
#endif