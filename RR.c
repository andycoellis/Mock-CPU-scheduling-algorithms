#include "RR.h"

void RR(struct List *list, char *filename) {
    FILE *f = fopen(filename, "w"); //File output to csv
    if (NULL == f) {
        exit(EXIT_FAILURE);
    }
    //Headers for .csv file
    fprintf(f, "PID,Burst Time,Arrival Time,Waiting Time,Turnaround Time\n");

    struct StdNode *ptr;
    struct StdNode *temp;
    struct List *currJobs = (struct List *) malloc(sizeof(struct List));

    double totalWait = 0;
    double totalTurnAround = 0;
    int processCount = 0;

    double clockCycle = 0;

    ptr = pop(list);
    currJobs->head_ref = create(ptr->id, ptr->burstTime, ptr->burstTime, ptr->arrivalTime);

    printf("\nBEGIN: Round Robin Processing...\n");
    while (!isEmpty(currJobs)) {
        ptr = pop(currJobs);    //Pop first ordered process to CPU

        ptr->burstRemain = ptr->burstRemain - 1;
        clockCycle += 1;

        if (ptr->burstRemain > 0) {
            ptr->burstRemain = ptr->burstRemain - 0.9;
        }
        clockCycle += 0.9;

        if (ptr->burstRemain <= 0) {
            printf("CPU_CLOCK[%.2f] PID[%d] BURST_REMAIN[%.2f]\n", clockCycle, ptr->id, ptr->burstRemain);
            fprintf(f, "%d,%d,%d,%.2f,%.2f\n",
                    ptr->id,
                    ptr->burstTime,
                    ptr->arrivalTime,
                    (clockCycle - ptr->arrivalTime) - ptr->burstTime, //waiting t = turnaround t - burst t
                    (clockCycle - ptr->arrivalTime)  //turnaround t = completion - arrival
            );
            totalWait += (clockCycle - ptr->arrivalTime) - ptr->burstTime;
            totalTurnAround += (clockCycle - ptr->arrivalTime);
            processCount++; //Count each new process to compute
        } else {
            //Find backlogged jobs and enter them into the queue
            while (!isEmpty(list) && peekArrival(list) < clockCycle) {
                temp = pop(list);
                if (isEmpty(currJobs)) {
                    currJobs->head_ref = create(temp->id, temp->burstTime, temp->burstTime, temp->arrivalTime);
                } else
                    push(currJobs, temp->id, temp->burstTime, temp->burstTime, temp->arrivalTime, false);
            }
            if (isEmpty(currJobs)) {
                free(currJobs->head_ref);
                currJobs->head_ref = create(ptr->id, ptr->burstTime, ptr->burstRemain, ptr->arrivalTime);
            } else
                push(currJobs, ptr->id, ptr->burstTime, ptr->burstRemain, ptr->arrivalTime, false);
        }
    }
    printf("END: Round Robin Processing");
    // Resulting averages
    printf("\nAverage wait time: [%.2f]\n", (totalWait / processCount));
    printf("Average turn around time: [%.2f]\n", (totalTurnAround / processCount));

    fclose(f);
}