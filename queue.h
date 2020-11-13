//
// Created by Andrew Ellis on 5/9/20.
//

#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#include "list.h"

struct StdNode* create(int id, int burstTime, double burstRemain, int arrivalTime);

bool push(struct List* list, int id, int burstTime, double burstRemain, int arrivalTime, bool priority);

struct StdNode* pop(struct List* list);

bool isEmpty(struct List* list);

int peekArrival(struct List* list);
#endif //UNTITLED_QUEUE_H
