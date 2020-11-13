#include "FCFS.h"

void FCFS(struct List *list, char *filename) {
    FILE *f = fopen(filename, "w"); //File output to csv
    if (NULL == f) {
        exit(EXIT_FAILURE);
    }
    //Headers for .csv file
    fprintf(f, "PID,Burst Time,Arrival Time,Waiting Time,Turnaround Time\n");

    struct StdNode *ptr;
    int clockCycle = 0;
    double totalWait = 0;
    double totalTurnAround = 0;
    int processCount = 0;

    printf("\nBEGIN: FCFS Processing...\n");
    while (!isEmpty(list)) {
        ptr = pop(list);    //Pop first ordered process to CPU
        int processTime = ptr->burstTime;
        processCount++; //Count each new process to compute

        while (processTime > 0) {   //Lifecycle of a process
            printf("CPU_CLOCK[%d] PROCESS[%d] BURST_REMAIN[%d]\n", clockCycle, ptr->id, processTime);
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

    }
    printf("END: First Come First Served Processing");
    // Resulting averages
    printf("\nAverage wait time: [%.2f]\n", (totalWait / processCount));
    printf("Average turn around time: [%.2f]\n", (totalTurnAround / processCount));

    fclose(f);
}