#include <stdio.h>
#include<string.h>

#include "queue.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"

void process(struct List *list, char *flag);

/*
 * Main function of scheduler, here we read in the original file
 */
int main(int argc, char *argv[]) {

    FILE *fp;
    char *line = NULL;
    char *filename;
    char *flag = NULL;
    size_t len = 0;
    ssize_t read;

    struct List *list = (struct List *) malloc(sizeof(struct List));
    list->head_ref = NULL;

    if (argc < 2) {
        printf("\n./task2 filename\n");
        return (1);
    } else
        filename = argv[1];

    if (argc > 2) {
        flag = argv[2];
    }
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("\nFile not found!\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char *tok = strtok(line, "\t");
        int id = atoi(tok);
        int burst = 0;
        int arrival = 0;

        while (tok != NULL) {
            tok = strtok(NULL, "\t"); // NULL instead of pointer
            if (NULL != tok) {
                burst = atoi(tok);
            }
            tok = strtok(NULL, "\n");
            if (NULL != tok) {
                arrival = atoi(tok);
            }
        }
        if (NULL == list->head_ref) {
            list->head_ref = create(id, burst, 0, arrival);
        } else
            push(list, id, burst, 0, arrival, false);

        free(tok);
        tok = NULL;
    }
    fclose(fp);

    process(list, flag);

    free(list);
    list = NULL;

    return 0;
}

/*
 * This is the processing function of the scheduler, will create a .csv of all analytics
 * of the individual structures performance
 */
void process(struct List *list, char *flag) {
    int algorithm = 0;
    char outFile[] = "output/data_fcfs.csv";
    /*
     * Check for flags, either priority scheduling or shortest burst priority
     * then assign the correct output filename.
     */
    if (flag != NULL) {
        if (strcmp(flag, "-s") == 0) {
            algorithm = 1;
            strcpy(outFile, "output/data_sjf.csv");
        } else if (strcmp(flag, "-r") == 0) {
            algorithm = 2;
            strcpy(outFile, "output/data_rr.csv");
        }
    }
    if (algorithm == 1) {
        SJF(list, outFile);
    } else if (algorithm == 2) {
        RR(list, outFile);
    } else
        FCFS(list, outFile);
}