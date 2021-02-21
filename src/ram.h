// Saad Shahbaz, McGill ID: 260845253
#include "pcb.h"
char *ram[1000];
extern int *start;
extern int *end;
void ram_initialize();
int addToRam(FILE *p, int *start1, int *end1);
void unloadingRam(PCB* pcb);