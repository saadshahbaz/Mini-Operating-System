// Saad Shahbaz, McGill ID: 260845253
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"

struct mem{
    char var[100];
    char var_value[200];
};

struct mem total[10000];

//extern int x;

int set(char*z, char*y){
    for(int i=0; i<x+1; i++){
        if(strcmp(total[i].var, z)==0){
            strcpy(total[i].var_value,y);
            x--;
            return 0;
        }
    }
    strcpy(total[x].var,z);
    strcpy(total[x].var_value,y);



    return 0;
}

int print(char*z){
    for(int i=0; i<x; i++){
        if(strcmp(total[i].var, z)==0){
            printf("%s\n",total[i].var_value);
            return 0;
        }
    }

    printf("Variable does not exist!!\n");
    return -1;
}
