// Saad Shahbaz, McGill ID: 260845253
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "kernel.h"
#include "cpu.h"

int *end = 0;
int *start = 0;

struct readyQueueNode{
    struct PCB *pcb;
    struct readyQueueNode *next;

};
struct readyQueueNode *head=NULL; 
struct readyQueueNode *tail= NULL;

void addToReady(PCB* pcb){
    struct readyQueueNode *current = (struct readyQueueNode*)malloc(sizeof(struct readyQueueNode));
    current->pcb = pcb;

    if(head ==NULL){
        head = current;
        tail=current;
        current->next = head;

    }else{
        tail->next = current;
        tail=current;
        tail->next=head;
    }
    
}

void remove_PCB_from_readyQueue(){
    struct readyQueueNode *current = (struct readyQueueNode*)malloc(sizeof(struct readyQueueNode));

    if(head==NULL){
        return;
    }else{
        if(head!=tail){
            head = head->next;
            tail->next= head;
            free(current);
        }else{
            head=tail=NULL;
            free(current);
        }
    }
}

PCB* getPCBfromQueue(){
    struct PCB *x = head->pcb;
    return x;
}


int myinit(char *filename){
    //return commands in it where it will perform functions will discuss later
    FILE *fp = fopen(filename, "r");
    if (fp ==NULL){
       printf("%s not found\n", filename);
        return -1;
    }

    //Adding it to the RAM
    int x = addToRam(fp, start, end);
    int final_end = *end;
    int final_start = *start;
    if(x==-1){
        return -1;
    }
    

    // Creating a PCB
    PCB* newPCB = makePCB(final_start, final_end);

    //adding the file to the ready queue
    (void) addToReady(newPCB);

    fclose(fp);
    return 0;
}


int scheduler(){
    while(1){
        int quanta= 2;
        struct PCB *currentPCB = getPCBfromQueue();
        assignPCB_PC(currentPCB);

        if((currentPCB->end)-(currentPCB->PC) > quanta){
            runn(quanta);
            remove_PCB_from_readyQueue();
            currentPCB->PC = currentPCB->PC+quanta;
            addToReady(currentPCB);
        }else{
            runn((currentPCB->end)-(currentPCB->PC));
            unloadingRam(currentPCB);
            remove_PCB_from_readyQueue();
            free(currentPCB);
        }

        if(head == NULL){
            break;
        }
    //getPCBfromQueue();
}   

    return 0;
}








int main(){

    ram_initialize();
    shellUI();

    return 0;
    //will execute stuff
}