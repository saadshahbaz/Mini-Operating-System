
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "shell.h"

struct CPU{
    int IP;
    char IR[10000];
    int quanta;
};

struct CPU *cpu;

int assignPCB_PC(PCB* pcb){

    if(cpu == NULL){
        cpu = (struct CPU*)malloc(sizeof(struct CPU));
    }

    cpu->IP = pcb->PC;
    return 0;
} 


int runn(int quanta){
    cpu->quanta = quanta;
    for(int i=cpu->IP; i < cpu->IP + cpu->quanta; i++){
        strcpy(cpu->IR, ram[i]);
        parse(cpu->IR);
        
    }
    return 0;
}
