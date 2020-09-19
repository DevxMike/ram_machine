#include "task_queue.h"

//FIFO queue

void copy_data_struct(task_queue_data_t* destination, const task_queue_data_t* source){ //copies stack/queue data
    strcpy(destination->command, source->command);
    strcpy(destination->operand_st, source->operand_st);
    destination->cmd_id = source->cmd_id;
}

task_queue_t* task_queue_init(size_t size){
    task_queue_t* temp = NULL;
    if((temp = (task_queue_t*)malloc(sizeof(task_queue_t))) != NULL){ //if alloc didnt fail
        temp->head = temp->tail = NULL;
        temp->max = size;
        temp->quantity = 0;
        return temp;
    }
    else{
        return NULL;
    }
}

bool task_queue_full(const task_queue_t* queue){ //returns bool val if queue is full
    return queue->quantity == queue->max;
}

bool task_queue_empty(const task_queue_t* queue){ //returns bool val if queue is empty
    if(queue){
        return queue->quantity == 0;
    }
    else return 1;
}

bool q_push(task_queue_t* queue, const task_queue_data_t* data){ //pushes an element to the end of the queue
    task_queue_element_t* temp = NULL;

    if(task_queue_full(queue) || ((temp = (task_queue_element_t*)malloc(sizeof(task_queue_element_t))) == NULL)){ //if queue is full or alloc failed
        return false;
    }
    else{
        copy_data_struct(&temp->data, data); //copy data to newly allocated memory
        if(task_queue_empty(queue)){ //if queue is empty
            queue->head = queue->tail = temp; //the very new memory is going to be our head and tail at once
        }
        else{
            queue->tail->next = temp; //else add item to the end of the queue
            queue->tail = queue->tail->next;
        }   
        queue->tail->next = NULL;
        ++queue->quantity; 
        return true;
    }
}

void print_queue_status(task_queue_t* queue){ //prints general info about queue
    printf("task_queue address: %p\nmax_size: %zu\nactual quantity: %zu\n", (void*)queue, queue->max, queue->quantity);
    printf("head address: %p\n", (void*)queue->head);
    if(task_queue_empty(queue)){
        printf("task queue is empty\n\n");
    }
    else if(task_queue_full(queue)){
        printf("task queue is full\n\n");
    }
    else{
        printf("task queue is not empty\n\n");
    }
}

task_queue_data_t* q_pop(task_queue_t* queue){ //pops first element from queue
    task_queue_data_t* temp = NULL;
    task_queue_element_t* head = NULL;

    if(task_queue_empty(queue) || (temp = (task_queue_data_t*)malloc(sizeof(task_queue_data_t))) == NULL){//if queue is empty or alloc failed
        return NULL;
    }
    else{
        head = queue->head; 
        copy_data_struct(temp, &head->data);//copy data from first item to newly allocated memory
        queue->head = queue->head->next; //move head to the next item
        --queue->quantity;
        free(head); //free unused memory
        return temp;
    }
}
