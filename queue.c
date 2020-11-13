//
// Created by Andrew Ellis on 5/9/20.
//
#include "queue.h"
struct StdNode *create(int id, int burstTime, double burstRemain,int arrivalTime) {

    struct StdNode *ptr = (struct StdNode *) malloc(sizeof(struct StdNode));

    if (NULL == ptr) {
        printf("\nstdnode failed to create\n");
        return NULL;
    }
    ptr->id = id;
    ptr->burstTime = burstTime;
    ptr->arrivalTime = arrivalTime;
    ptr->burstRemain = burstRemain;
    ptr->next = NULL;

    return ptr;
}
/*
 * Append all new entries to the tail of the structure
 */
bool push(struct List* list, int id, int burstTime, double burstRemain, int arrivalTime, bool priority) {

    struct StdNode *ptr = (struct StdNode *) malloc(sizeof(struct StdNode));
    struct StdNode *curr = NULL;
    struct StdNode *prev = NULL;

    if (NULL == ptr) {
        printf("\nlist failed to create");
        return NULL;
    }
    ptr->id = id;
    ptr->burstTime = burstTime;
    ptr->burstRemain = burstRemain;
    ptr->arrivalTime = arrivalTime;
    ptr->next = NULL;

    curr = list->head_ref;

    bool found = false;
    while (!found) {
        if(priority && burstTime < curr->burstTime){
            if(NULL == prev){
                list->head_ref = ptr;
                list->head_ref->next = curr;
                found = true;
            }
            else{
                ptr->next = curr;
                prev->next = ptr;
                found = true;
            }
        }
        if(!found && NULL == curr->next){
            curr->next = ptr;
            found = true;
        }
        else if(!found){
            prev = curr;
            curr = curr->next;
        }
    }
    curr = NULL;
    prev = NULL;
    ptr = NULL;
    return found;
}
/*
 * Remove and return the head node
 *
 */
struct StdNode *pop(struct List* list) {
    if (NULL == list->head_ref) {
        printf("\nList is empty\n");
        return NULL;
    }
    struct StdNode *item = NULL;

    if (NULL == list->head_ref->next) {
        item = list->head_ref;
        list->head_ref = NULL;
    }
    else {
        item = list->head_ref;
        list->head_ref = list->head_ref->next;
    }
    item->next = NULL;
    return item;
}

bool isEmpty(struct List* list) {
    bool response = false;
    if (NULL == list->head_ref) {
        response = true;
    }
    return response;
}

int peekArrival(struct List* list){
    int result = -1;

    if(NULL != list->head_ref){
        result = list->head_ref->arrivalTime;
    }
    return result;
}