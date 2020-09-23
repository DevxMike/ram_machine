#include "main.h"
#include "loop.h"
#include "loop_heap.h"
#include <time.h>
#include "loop_pointers.h"

int main(int argc, char** argv){
    ram_cell_t R0 = {
        0, 0
    };
    main_vars_t main_vars;
    task_queue_element_t* temp;
    clock_t c1, c2;
    int index;
    init_main(&main_vars);
    if(argc == 1){ //if argv contains program name only
        printf("Wrong usage. Try %s <file_name>.txt or %s -h for help\n", argv[0], argv[0]);
        exit_w_code(NO_FILE_NAME_ERR);
    }
    else{
        
        if(strcmp(argv[1], "-h") == 0){ //if argv contains program name and "-h" string 
            print_help(argv[0], COMMAND_ROW, commands, COMMAND_ROW, ex_operands);
            exit_w_code(main_vars.EXIT_CODE);
        } 
        else if(has_invalid_chars(argv[1], "txt")){ //if <file_name> string has forbidden chars
            exit_w_code(FILE_NAME_ERR);
        }

        printf("file to be read: %s\n", argv[1]);

        if((main_vars.task_arr.task_arr = read_file(argv[1], &main_vars.task_arr.arr_size, &main_vars.EXIT_CODE)) != NULL && main_vars.task_arr.arr_size > 0){
            if(((main_vars.ram_heap = init_ram_heap()) == NULL)){ //init heap used to heap-sort ram chip
                exit_w_code(HEAP_INIT_ERR);
            }
            if((main_vars.ram_chip = init_ram()) == NULL){ //init ram chip
                exit_w_code(RAM_INIT_ERR);
            }
            if((main_vars.queue = task_queue_init(main_vars.task_arr.arr_size)) == NULL){ //safety, it`s better to have more "place", can be easilly changed 
                exit_w_code(TASK_QUEUE_INIT_ERR);
            }

            ram_push(main_vars.ram_chip, &R0); //add special register to ram chip

            c1 = clock();
            for(size_t i = 0; i < main_vars.task_arr.arr_size; ++i){
                if(DataTypeAnalyzer(&main_vars.data, main_vars.task_arr.task_arr[i])){
                    if(Interpreter(&main_vars.data, main_vars.queue, &main_vars.loops, &main_vars.EXIT_CODE, i) == 1){
                        main_vars.input.data_arr = input_data(main_vars.data.data, &main_vars.EXIT_CODE, &main_vars.input.arr_size);
                    } 
                    if(main_vars.EXIT_CODE){
                        //free task queue
                        if(!task_queue_empty(main_vars.queue)){
                            while(main_vars.queue->head != NULL){
                                temp = main_vars.queue->head;
                                main_vars.queue->head = main_vars.queue->head->next;
                                free(temp);
                            }
                        }  
                       for(size_t i = 0; i < main_vars.task_arr.arr_size; ++i){
                            free(main_vars.task_arr.task_arr[i]);
                        }
                        free(main_vars.task_arr.task_arr);
                        free(main_vars.ram_chip->arr);
                        free(main_vars.ram_chip);
                        free(main_vars.ram_heap->arr);
                        free(main_vars.ram_heap);
                        free(main_vars.queue); 
                        exit_w_code(main_vars.EXIT_CODE); //syntax err
                    }
                }
                else{
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                        //free task queue
                        if(!task_queue_empty(main_vars.queue)){
                            while(main_vars.queue->head != NULL){
                                temp = main_vars.queue->head;
                                main_vars.queue->head = main_vars.queue->head->next;
                                free(temp);
                            }
                        }  
                       for(size_t i = 0; i < main_vars.task_arr.arr_size; ++i){
                            free(main_vars.task_arr.task_arr[i]);
                        }
                        free(main_vars.task_arr.task_arr);
                        free(main_vars.ram_chip->arr);
                        free(main_vars.ram_chip);
                        free(main_vars.ram_heap->arr);
                        free(main_vars.ram_heap);
                        free(main_vars.queue); 
                    exit_w_code(WRONG_SYNTAX_ERR);
                    /*----------------------------------------------if failed free memory section -----------------------------------------------*/
                }
            }
            c2 = clock();
            printf("\nSyntax correct.\nInterpretation time: %lfs\nProgram output:\n\n", (double)(c2 - c1)/CLOCKS_PER_SEC);
            if(main_vars.loops.temp_loop != NULL){
    			add_to_loop_container(main_vars.loops.loops_array, main_vars.loops.temp_loop, main_vars.loops.heap);
            }
            loop_heap_sort(main_vars.loops.loops_array, main_vars.loops.heap);
            /*temp = main_vars.queue->head;
            while(temp){
                printf("%s %s\n", temp->data.command, temp->data.operand_st);
                temp = temp->next;
            }*/

            for(size_t i = 0; i < main_vars.loops.loop_pointers->quantity; ++i){
                loop_pointer_t* temp = main_vars.loops.loop_pointers->arr[i];
                temp->pointer = search_loop(
                    main_vars.loops.loops_array, temp->next_cmd->data.operand_st, 0, main_vars.loops.loops_array->quantity - 1
                );
                temp->next_cmd = temp->next_cmd->next;
            }
            
            sort_pointers(main_vars.loops.loop_pointers, main_vars.loops.pointers_heap);

            c1 = clock();
            temp = main_vars.queue->head;

            while(temp && strcmp(temp->data.command, "HALT")){
                if(is_loop(temp->data.cmd_id) && is_loop_condition_met(main_vars.ram_chip, temp->data.cmd_id)){ //if cmd is a jump to label and condition is met
                    loop_manager(
                        main_vars.ram_chip, 
                        main_vars.ram_heap, 
                        search_loop(main_vars.loops.loops_array, 
                        temp->data.operand_st, 0, main_vars.loops.loops_array->quantity - 1), 
                        &main_vars.input
                    ); //perform loop
                    temp = get_pointer(main_vars.loops.loop_pointers, temp->data.operand_st)->next_cmd;
                    continue;
                }
                tasker(main_vars.ram_chip, &temp->data, main_vars.ram_heap, &main_vars.input);
                temp = temp->next;
            }
            c2 = clock();           
        }
        else{
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            //free task queue
            if(!task_queue_empty(main_vars.queue)){
                while(main_vars.queue->head != NULL){
                    temp = main_vars.queue->head;
                    main_vars.queue->head = main_vars.queue->head->next;
                    free(temp);
                }
            }  
            for(size_t i = 0; i < main_vars.task_arr.arr_size; ++i){
                free(main_vars.task_arr.task_arr[i]);
            }
            free(main_vars.task_arr.task_arr);
            free(main_vars.ram_chip);
            free(main_vars.ram_heap);
            free(main_vars.queue); 
            /*----------------------------------------------if failed free memory section -----------------------------------------------*/
            exit_w_code(main_vars.EXIT_CODE);
        }


        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        //free task queue
        if(!task_queue_empty(main_vars.queue)){
            while(main_vars.queue->head != NULL){
                temp = main_vars.queue->head;
                main_vars.queue->head = main_vars.queue->head->next;
                free(temp);
            }
        }  
        for(size_t i = 0; i < main_vars.task_arr.arr_size; ++i){
            free(main_vars.task_arr.task_arr[i]);
        }
        free(main_vars.task_arr.task_arr);
        free(main_vars.ram_chip->arr);
        free(main_vars.ram_chip);
        free(main_vars.ram_heap->arr);
        free(main_vars.ram_heap);
        free(main_vars.queue); 
        /*----------------------------------------------------free memory section----------------------------------------------------------*/
        printf("\nProgram duration: %lfs", (double)(c2 - c1)/CLOCKS_PER_SEC);
        exit_w_code(main_vars.EXIT_CODE);
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
    vars->loops.temp_loop = (loop_t*) malloc(sizeof(loop_t));
    vars->loops.loop_pointers = init_pointers();
    vars->loops.pointers_heap = init_pointers();
}