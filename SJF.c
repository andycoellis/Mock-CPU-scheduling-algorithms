#include "SJF.h"

void SJF(struct List *list, char *filename) {
    FILE *f = fopen(filename, "w"); //File output to csv
    if (NULL == f) {
        exit(EXIT_FAILURE);
    }
    //Headers for .csv file
    fprintf(f, "PID,Burst Time,Arrival Time,Waiting Time,Turnaround Time\n");

    struct StdNode *ptr;
    struct List *currJobs;
    int clockCycle = 0;
    double totalWait = 0;
    double totalTurnAround = 0;
    int processCount = 0;
    /*
     * This list will be all available jobs in priority of shortest job
     */

    currJobs = (struct List *) malloc(sizeof(struct List));
    ptr = pop(list);
    //Assign first arrived job to the new growing priority list
    currJobs->head_ref = create(ptr->id, ptr->burstTime, 0, ptr->arrivalTime);

    printf("\nBEGIN: Shortest Job First Processing...\n");
    while (!isEmpty(currJobs)) {
        ptr = pop(currJobs);    //Pop first ordered process to CPU
        int processTime = ptr->burstTime;
        processCount++; //Count each new process to compute
        while (processTime > 0) {   //Lifecycle of a process
            printf("CPU_CLOCK[%d] PID[%d] BURST_REMAIN[%d]\n", clockCycle, ptr->id, processTime);
            clockCycle++;
            processTime--;
        }
        //Row input for .csv
        fprintf(f, "%d,%d,%d,%.2d,%.2d\n",
                ptr->id,
                ptr->burstTime,
                ptr->arrivalTime,
                (clockCycle - ptr->arrivalTime) - ptr->burstTime, //waiting t = turnaround t - burst t
                (clockCycle - ptr->arrivalTime)  //turnaround t = completion - arrival
        );
        totalWait += (clockCycle - ptr->arrivalTime) - ptr->burstTime;
        totalTurnAround += (clockCycle - ptr->arrivalTime);

        bool searchComplete = false;
        while (!searchComplete) {
            struct StdNode *temp;
            if (isEmpty(list) || peekArrival(list) > clockCycle) {
                searchComplete = true;
            } else {
                temp = pop(list);
                if (isEmpty(currJobs)) {
                    currJobs->head_ref = create(temp->id, temp->burstTime, 0, temp->arrivalTime);
                } else
                    push(currJobs, temp->id, temp->burstTime, 0, temp->arrivalTime, true);
            }
        }
    }
    printf("END: Shortest Job First Processing");
    // Resulting averages
    printf("\nAverage wait time: [%.2f]\n", (totalWait / processCount));
    printf("Average turn around time: [%.2f]\n", (totalTurnAround / processCount));

    fclose(f);

    free(currJobs);
    currJobs = NULL;
}