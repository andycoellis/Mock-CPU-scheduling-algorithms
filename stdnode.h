//
// Created by Andrew Ellis on 5/9/20.
//

#ifndef UNTITLED_STDNODE_H
#define UNTITLED_STDNODE_H
struct StdNode {
    int id;
    int burstTime;
    double burstRemain;
    int arrivalTime;

    struct StdNode *next;
};
#endif //UNTITLED_STDNODE_H
