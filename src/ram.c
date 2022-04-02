
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ram.h"


void ram_initialize(){
    for(int i=0; i<1000; i++){
        ram[i] = NULL;
    }
}

int addToRam(FILE *p, int *start1, int *end1){
    //TODO: CHECK FOR THE END OF RAM
    //printf("%d",&start);
    char num[1000];
    int i=-1;
    for(int x=0; x<10000; x++){
        if(ram[x]==NULL){
            i=x;
            break;
        }
    }

    if(i==-1){
        printf("ERROR: Not enough RAM to add program.”\n");
        return -1;
    }

    int start_of_pcb = i;
    start1 = &start_of_pcb;

    while(!feof(p)){
        fgets(num, 999,p);
        ram[i] = strdup(num);
        i++;
    }
    end1 = &i;

    start = start1;
    end = end1;

    return 0;
}



void unloadingRam(PCB* pcb){
    //TODO: UNLOAD THE RAM WHEN A PCB IS REMOVED
    for(int i=pcb->start; i<pcb->end; i++){
        ram[i] = NULL;
    }
}







