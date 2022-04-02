
#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "ram.h"

typedef struct PCB PCB;


PCB* makePCB(int start, int end){ 
    //TODO: Please assign the PC value later
    struct PCB *new_PCB;

    new_PCB = (struct PCB*) malloc(sizeof(struct PCB));

    new_PCB->PC=start;
    new_PCB->start = start;
    new_PCB->end = end;


    return new_PCB;

}

