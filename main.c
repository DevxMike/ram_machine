#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "stack.h"
#include "task_queue.h"
#include <string.h>
#include "reader.h"
#include <stdbool.h>
#include "errors.h"
#include "syntax.h"

int main(int argc, char** argv){
    for(int i = 0; i < COMMAND_ROW; ++i){ //just for debug
        	    printf("command: %s, index: %d\n", commands[i], search_command(commands[i], 0, COMMAND_ROW, COMMAND_ROW/2));
            }
    unsigned EXIT_CODE = 0;
    char* m_str;
    call_stack_t* call_stack = NULL;
    task_queue_t* task_queue = NULL;
    task_queue_element_t* temp;
    AnalyzedData data;
    size_t task_arr_size = 0;
    char** task_arr;
    char* free_str_ptr;

    if(argc == 1){ //if argv contains program name only
        printf("Wrong usage. Try %s <file_name>.txt or %s -h for help\n", argv[0], argv[0]);
        exit_w_code(NO_FILE_NAME_ERR);
    }
    else{
        
        if(strcmp(argv[1], "-h") == 0){ //if argv contains program name and "-h" string 
            //printf("Some help message\n");
            print_help(argv[0], COMMAND_ROW, commands, COMMAND_ROW, ex_operands);
            exit_w_code(EXIT_CODE);
        } 
        else if(has_invalid_chars(argv[1], "txt")){ //if <file_name> string has forbidden chars
            exit_w_code(FILE_NAME_ERR);
        }

        if((call_stack = init_stack(50)) == NULL){
            exit_w_code(STACK_INIT_ERR);
        }
        if((task_queue = task_queue_init(50)) == NULL){
            free(call_stack); //if init failed, free allocated memory
            exit_w_code(TASK_QUEUE_INIT_ERR);
        }

        printf("file to be read: %s\n\n", argv[1]);
        
        if((task_arr = read_file(argv[1], &task_arr_size, &EXIT_CODE)) != NULL && task_arr_size > 0){
            for(size_t i = 0; i < task_arr_size; ++i){
                if(DataTypeAnalyzer(&data, task_arr[i])){
                    Interpreter(&data);
                    printf("\n");
                }
                else{
                    free(call_stack->data);//free memory
                    free(call_stack);
                    for(size_t i = 0; i < task_arr_size; ++i){
                        free(task_arr[i]);
                    }
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                    free(task_arr);
                    //free task queue
                    if(!task_queue_empty(task_queue)){
                        while(task_queue->head != NULL){
                            temp = task_queue->head;
                            task_queue->head = task_queue->head->next;
                            free(temp);
                        }
                    }  
                    for(size_t i = 0; i < task_arr_size; ++i){
                        free(task_arr[i]);
                    }
                    free(task_arr);
                    free(task_queue); 
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                    exit_w_code(WRONG_SYNTAX_ERR);
                }
            }
        }
        else{
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/

            free(call_stack->data);//free memory
            free(call_stack);
            //free task queue
            if(!task_queue_empty(task_queue)){
                while(task_queue->head != NULL){
                    temp = task_queue->head;
                    task_queue->head = task_queue->head->next;
                    free(temp);
                }
            }  
            free(task_queue); 
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            exit_w_code(EXIT_CODE);
        }


        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        free(call_stack->data);//free memory
        free(call_stack);
        for(size_t i = 0; i < task_arr_size; ++i){
            free(task_arr[i]);
        }
        free(task_arr);
            //free task queue
        if(!task_queue_empty(task_queue)){
            while(task_queue->head != NULL){
                temp = task_queue->head;
                task_queue->head = task_queue->head->next;
                free(temp);
            }
        }  
        free(task_queue); 
        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        exit_w_code(EXIT_CODE);  
    }    
}