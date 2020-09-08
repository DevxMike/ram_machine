#include "main.h"
#include "loop.h"
#include "loop_heap.h"



int main(int argc, char** argv){
    ram_cell_t R0 = {
        0, 0
    };
    main_vars_t program_variables;
    task_queue_data_t* t_data = NULL;

    if(argc == 1){ //if argv contains program name only
        printf("Wrong usage. Try %s <file_name>.txt or %s -h for help\n", argv[0], argv[0]);
        exit_w_code(NO_FILE_NAME_ERR);
    }
    else{
        
        if(strcmp(argv[1], "-h") == 0){ //if argv contains program name and "-h" string 
            print_help(argv[0], COMMAND_ROW, commands, COMMAND_ROW, ex_operands);
            exit_w_code(program_variables.EXIT_CODE);
        } 
        else if(has_invalid_chars(argv[1], "txt")){ //if <file_name> string has forbidden chars
            exit_w_code(FILE_NAME_ERR);
        }

        printf("file to be read: %s\n", argv[1]);

        if((program_variables.task_arr.task_arr = read_file(argv[1], &program_variables.task_arr.arr_size, &program_variables.EXIT_CODE)) != NULL && program_variables.task_arr.arr_size > 0){
            if(((program_variables.ram_heap = init_ram_heap()) == NULL)){ //init heap used to heap-sort ram chip
                exit_w_code(HEAP_INIT_ERR);
            }
            if((program_variables.ram_chip = init_ram()) == NULL){ //init ram chip
                exit_w_code(RAM_INIT_ERR);
            }
            if((program_variables.queue = task_queue_init(program_variables.task_arr.arr_size)) == NULL){ //safety, it`s better to have more "place", can be easilly changed 
                exit_w_code(TASK_QUEUE_INIT_ERR);
            }

            ram_push(program_variables.ram_chip, &R0); //add special register to ram chip

            for(size_t i = 0; i < program_variables.task_arr.arr_size; ++i){
                if(DataTypeAnalyzer(&program_variables.data, program_variables.task_arr.task_arr[i])){
                    if(Interpreter(&program_variables.data, program_variables.queue, &program_variables.EXIT_CODE, i) == 1){
                        program_variables.input.data_arr = input_data(program_variables.data.data, &program_variables.EXIT_CODE, &program_variables.input.arr_size);
                    } 
                    if(program_variables.EXIT_CODE){
                        //free task queue
                        if(!task_queue_empty(program_variables.queue)){
                            while(program_variables.queue->head != NULL){
                                temp = program_variables.queue->head;
                                program_variables.queue->head = program_variables.queue->head->next;
                                free(temp);
                            }
                        }  
                       for(size_t i = 0; i < program_variables.task_arr.arr_size; ++i){
                            free(program_variables.task_arr.task_arr[i]);
                        }
                        free(program_variables.task_arr.task_arr);
                        free(program_variables.ram_chip->arr);
                        free(program_variables.ram_chip);
                        free(program_variables.ram_heap->arr);
                        free(program_variables.ram_heap);
                        free(program_variables.queue); 
                        exit_w_code(program_variables.EXIT_CODE); //syntax err
                    }
                }
                else{
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                        //free task queue
                        if(!task_queue_empty(program_variables.queue)){
                            while(program_variables.queue->head != NULL){
                                temp = program_variables.queue->head;
                                program_variables.queue->head = program_variables.queue->head->next;
                                free(temp);
                            }
                        }  
                       for(size_t i = 0; i < program_variables.task_arr.arr_size; ++i){
                            free(program_variables.task_arr.task_arr[i]);
                        }
                        free(program_variables.task_arr.task_arr);
                        free(program_variables.ram_chip->arr);
                        free(program_variables.ram_chip);
                        free(program_variables.ram_heap->arr);
                        free(program_variables.ram_heap);
                        free(program_variables.queue); 
                    exit_w_code(WRONG_SYNTAX_ERR);
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                }
            }
            printf("\nSyntax correct.\nProgram output:\n\n");
            while(!task_queue_empty(program_variables.queue)){
                t_data = q_pop(program_variables.queue);
                tasker(program_variables.ram_chip, t_data, program_variables.ram_heap, &program_variables.input);
                free(t_data);
            }
        }
        else{
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            //free task queue
            if(!task_queue_empty(program_variables.queue)){
                while(program_variables.queue->head != NULL){
                    temp = program_variables.queue->head;
                    program_variables.queue->head = program_variables.queue->head->next;
                    free(temp);
                }
            }  
            for(size_t i = 0; i < program_variables.task_arr.arr_size; ++i){
                free(program_variables.task_arr.task_arr[i]);
            }
            free(program_variables.task_arr.task_arr);
            free(program_variables.ram_chip->arr);
            free(program_variables.ram_chip);
            free(program_variables.ram_heap->arr);
            free(program_variables.ram_heap);
            free(program_variables.queue); 
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            exit_w_code(program_variables.EXIT_CODE);
        }


        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        //free task queue
        if(!task_queue_empty(program_variables.queue)){
            while(program_variables.queue->head != NULL){
                temp = program_variables.queue->head;
                program_variables.queue->head = program_variables.queue->head->next;
                free(temp);
            }
        }  
        for(size_t i = 0; i < program_variables.task_arr.arr_size; ++i){
            free(program_variables.task_arr.task_arr[i]);
        }
        free(program_variables.task_arr.task_arr);
        free(program_variables.ram_chip->arr);
        free(program_variables.ram_chip);
        free(program_variables.ram_heap->arr);
        free(program_variables.ram_heap);
        free(program_variables.queue); 
        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        exit_w_code(program_variables.EXIT_CODE);
    }    
}
void init_main(main_vars_t* vars){
    vars->EXIT_CODE = 0;
    vars->input.data_arr = NULL;
    vars->queue = NULL;
    vars->ram_chip = NULL;
    vars->ram_heap = NULL;
    vars->task_arr.task_arr = NULL;
    vars->input.arr_size = vars->input.element = vars->task_arr.arr_size = 0;  
    vars->loops.heap = init_loop_heap();
    vars->loops.loops_array = init_loop();
}