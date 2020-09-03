#include "loop_list.h"
#include <stdlib.h>
#include "errors.h"
void push_back(list_element_t** head, const list_data_t* data){
    list_element_t* iter = NULL;
        if(*head == NULL){
            *head = (list_element_t*)malloc(sizeof(list_element_t));
            copy_data_struct(&(*head)->data, data);
            (*head)->next = NULL;
        }
        else{
            iter = *head;
            while(iter->next != NULL){
                iter = iter->next;
            }
            iter->next = (list_element_t*)malloc(sizeof(list_element_t));
            copy_data_struct(&iter->next->data, data);
            iter->next->next = NULL;
        }
}
void free_list(list_element_t** head){
    list_element_t* temp = NULL;
    while(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void copy_list(list_element_t** dst, const list_element_t* src){
    if(src != NULL){
        push_back(dst, &src->data);
        copy_list(dst, src->next);
    }
}