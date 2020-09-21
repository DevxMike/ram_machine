#include "loop_list.h"
#include <stdlib.h>
#include "errors.h"
void push_back(list_element_t** head, const list_data_t* data){
    list_element_t* iter;
    if(data != NULL && strlen(data->command) && strlen(data->operand_st)){
        iter = (list_element_t*)malloc(sizeof(list_element_t));
        if((*head) == NULL){ //if list is empty
            copy_data_struct(&iter->data, data); //add an element
            iter->next = NULL; //head is first and last element
            *head = iter;
        }
        else{
            iter = *head; 
            while(iter->next != NULL){
                iter = iter->next; //search for last element
            }
            iter->next = (list_element_t*)malloc(sizeof(list_element_t)); //allocate memory for new element
            copy_data_struct(&(iter->next->data), data); //copy data
            iter->next->next = NULL; //end the list
        }
    }
}
void free_list(list_element_t** head){
    list_element_t* temp = NULL; //temp iterator
    while(*head != NULL){ //while there is an element in the list
        temp = *head;
        *head = (*head)->next;
        free(temp); //free memory
    }
}
void copy_list(list_element_t** dst, const list_element_t* const src){
    if(src != NULL){ //while src points to an element (not an end of the list)
        push_back(dst, &src->data); //push an element to dst list
        copy_list(dst, src->next); //continue while not null
    }
}