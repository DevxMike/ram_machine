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
#include "ram.h"
#include "ram_heap.h"

const size_t arr_size = 11;
ram_cell_t cells[] = {
    {15,1},
    {21,1},
    {3,1},
    {6,1},
    {8,1},
    {1000000,1},
    {12,1},
    {11,1},
    {5, 1},
    {4, 1},
    {2, 1}
};

int main(int argc, char** argv){
    unsigned EXIT_CODE = 0;
    char* m_str;
    call_stack_t* call_stack = NULL;
    task_queue_t* task_queue = NULL;
    task_queue_element_t* temp;
    task_queue_data_t* t_data = NULL;
    AnalyzedData data;
    size_t task_arr_size = 0, input_data_size = 0;
    char** task_arr = NULL;
    int* input_tab = NULL;
    bool empty_input = true;

    ram_heap_t* ram_heap = NULL;
    ram_chip_t* ram_chip = NULL;

    ram_heap = init_ram_heap();
    ram_chip = init_ram();
    /*
    //--------------------------------------it`s just debug---------------------------------------
    printf("\n\n--------------------debug functionality--------------------\n\n");
    char test[] = "21 33 1 23 32";

    if((input_tab = input_data(test, &EXIT_CODE, &input_data_size)) == NULL){
        if(EXIT_CODE){
            exit_w_code(EXIT_CODE);
        }
        //else input is empty and there is no need to abort program
    }
    
    for(size_t i = 0; i < input_data_size; ++i){
        printf("Input integer: %d\n", input_tab[i]);
    }
    printf("\n----------------------------end----------------------------\n\n");
    //--------------------------------------it`s just debug---------------------------------------
    */


    if(argc == 1){ //if argv contains program name only
        printf("Wrong usage. Try %s <file_name>.txt or %s -h for help\n", argv[0], argv[0]);
        exit_w_code(NO_FILE_NAME_ERR);
    }
    else{
        
        if(strcmp(argv[1], "-h") == 0){ //if argv contains program name and "-h" string 
            print_help(argv[0], COMMAND_ROW, commands, COMMAND_ROW, ex_operands);
            exit_w_code(EXIT_CODE);
        } 
        else if(has_invalid_chars(argv[1], "txt")){ //if <file_name> string has forbidden chars
            exit_w_code(FILE_NAME_ERR);
        }

        if(has_loops){ 
            if((call_stack = init_stack(50)) == NULL){
                exit_w_code(STACK_INIT_ERR);
            }
        }
        printf("file to be read: %s\n\n", argv[1]);
        
        if((task_arr = read_file(argv[1], &task_arr_size, &EXIT_CODE)) != NULL && task_arr_size > 0){
            if((task_queue = task_queue_init(task_arr_size)) == NULL){ //safety, it`s better to have more "place", can be easilly changed 
                free(call_stack); //if init failed, free allocated memory
                exit_w_code(TASK_QUEUE_INIT_ERR);
            }

            for(size_t i = 0; i < task_arr_size; ++i){
                if(DataTypeAnalyzer(&data, task_arr[i])){
                    Interpreter(&data, task_queue, &EXIT_CODE, i); 
                    if(EXIT_CODE){
                        exit_w_code(EXIT_CODE); //syntax err
                        if(call_stack != NULL){
                        free(call_stack->data);//free memory
                        free(call_stack);
                        }
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
                        for(size_t i = 0; i < task_arr_size; ++i){
                            free(task_arr[i]);
                        }
                        free(task_arr);
                        free(task_queue); 
                    }
                }
                else{
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                    if(call_stack != NULL){
                        free(call_stack->data);//free memory
                        free(call_stack);
                    }
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
                    for(size_t i = 0; i < task_arr_size; ++i){
                        free(task_arr[i]);
                    }
                    free(task_arr);
                    free(task_queue); 
                    exit_w_code(WRONG_SYNTAX_ERR);
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                }
            }
            while(!task_queue_empty(task_queue)){
                t_data = q_pop(task_queue);
                printf("CMD: %s, OPERAND: %s, CMD_ID: %d\n", t_data->command, t_data->operand_st, t_data->cmd_id);
                free(t_data);
            }
        }
        else{
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            if(call_stack != NULL){
                free(call_stack->data);//free memory
                free(call_stack);
            }
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
        if(call_stack != NULL){
                free(call_stack->data);//free memory
                free(call_stack);
        }
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