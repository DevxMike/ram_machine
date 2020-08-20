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

ram_cell_t R0 = {
    0, 0
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

    ram_heap_t* ram_heap = NULL, *ram_heap_copy = NULL;
    ram_chip_t* ram_chip = NULL;


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
            if(((ram_heap = init_ram_heap()) == NULL) || ((ram_heap_copy = init_ram_heap()) == NULL)){ //init heap used to heap-sort ram chip
                exit_w_code(HEAP_INIT_ERR);
            }
            if((ram_chip = init_ram()) == NULL){ //init ram chip
                exit_w_code(RAM_INIT_ERR);
            }
            if((task_queue = task_queue_init(task_arr_size)) == NULL){ //safety, it`s better to have more "place", can be easilly changed 
                exit_w_code(TASK_QUEUE_INIT_ERR);
            }

            ram_push(ram_chip, &R0); //add special register to ram chip
            ram_heap_push(ram_heap_copy, &R0, &EXIT_CODE); //only one register available, no need to sort 

            for(size_t i = 0; i < task_arr_size; ++i){
                if(DataTypeAnalyzer(&data, task_arr[i])){
                    if(Interpreter(&data, task_queue, &EXIT_CODE, i) == 1){
                        input_tab = input_data(data.data, &EXIT_CODE, &input_data_size);
                    } 
                    if(EXIT_CODE){
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
                        free(ram_chip->arr);
                        free(ram_chip);
                        free(ram_heap_copy->arr);
                        free(ram_heap_copy);
                        free(ram_heap->arr);
                        free(ram_heap);
                        free(task_arr);
                        free(task_queue); 
                        exit_w_code(EXIT_CODE); //syntax err
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
                    free(ram_chip->arr);
                    free(ram_chip);
                    free(ram_heap_copy->arr);
                    free(ram_heap_copy);
                    free(ram_heap->arr);
                    free(ram_heap);
                    free(task_arr);
                    free(task_queue); 
                    exit_w_code(WRONG_SYNTAX_ERR);
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                }
            }
            while(!task_queue_empty(task_queue)){
                t_data = q_pop(task_queue);
                tasker(ram_chip, t_data);
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
            free(ram_chip->arr);
            free(ram_chip);
            free(ram_heap_copy->arr);
            free(ram_heap_copy);
            free(ram_heap->arr);
            free(ram_heap);
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
        free(ram_chip->arr);
        free(ram_chip);
        free(ram_heap_copy->arr);
        free(ram_heap_copy);
        free(ram_heap->arr);
        free(ram_heap); 
        free(task_queue); 
        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        exit_w_code(EXIT_CODE);  
    }    
}