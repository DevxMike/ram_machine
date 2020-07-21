#include "task_queue.h"

task_queue_t* task_queue_init(size_t size){
    task_queue_t* temp = NULL;
    if((temp = (task_queue_t*)malloc(sizeof(task_queue_t))) != NULL){
        temp->head = temp->tail = NULL;
        temp->max = size;
        temp->quantity = 0;
        return temp;
    }
    else{
        return NULL;
    }
}

bool task_queue_full(const task_queue_t* queue){
    return queue->quantity == queue->max;
}

bool task_queue_empty(const task_queue_t* queue){
    return queue->quantity == 0;
}

bool push(task_queue_t* queue, const task_queue_data_t* data){
    task_queue_element_t* temp = NULL;

    if(task_queue_full(queue) || ((temp = (task_queue_element_t*)malloc(sizeof(task_queue_element_t))) == NULL)){
        return false;
    }
    else{
        copy_data_struct(&temp->data, data);
        if(task_queue_empty(queue)){
            queue->head = queue->tail = temp;
        }
        else{
            queue->tail->next = temp;
            queue->tail = queue->tail->next;
        }   
        ++queue->quantity;
        return true;
    }
}

void print_queue_status(task_queue_t* queue){
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

task_queue_data_t* pop(task_queue_t* queue){
    task_queue_data_t* temp = NULL;
    task_queue_element_t* head = NULL;

    if(task_queue_empty(queue) || (temp = (task_queue_data_t*)malloc(sizeof(task_queue_data_t))) == NULL){
        return NULL;
    }
    else{
        head = queue->head;
        copy_data_struct(temp, &head->data);
        queue->head = queue->head->next;
        --queue->quantity;
        free(head);
        return temp;
    }
}