
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "shell.h"
#include "kernel.h"


int x = 0;
extern struct mem total;

int run(char* x){
    char *FileName = x;
    FILE *fp = fopen(FileName, "r");

    if (fp ==NULL){
       printf("Script not found\n");
        return -1;
    }
    char input[1000];

    while (fgets(input, sizeof(input), fp))
    {
        
        int errorcode=0;

        char *ptr = input;
        char *args[100];

        errorcode = parse(input);

        if(errorcode==2 || errorcode ==3 || errorcode==1){
            break;
        }else if(errorcode == -1){
            continue;
        }

    }
    
    fclose(fp);
    return 0;
}   

int exec(char *words[], int no_var){
    if(no_var == 1){
       int x =  myinit(words[1]);

       if(x!=-1){
         scheduler();
       }
       else{
           return 2;
       }
        
    }
    if(no_var==2){
        if(strcmp(words[1],words[2])==0){
            printf("Error: %s already loaded\n",words[2]);
            return 2;

        }else{
            int x1= myinit(words[1]);
            int x2 = myinit(words[2]);
            if(x1 !=-1 & x2 != -1){
                 scheduler();
            }else{
                return 2;
            }
               
        }
    }
    if(no_var==3){
        if(strcmp(words[1],words[2])==0){
            printf("Error: %s already loaded\n",words[2]);
            return 2;

        }else if(strcmp(words[1],words[3])==0){
            printf("Error: %s already loaded\n",words[3]);
            return 2;

        }else if(strcmp(words[2],words[3])==0){
            printf("Error: %s already loaded\n",words[3]);
            return 2;

        }else{
            int x1= myinit(words[1]);
            int x2 = myinit(words[2]);
            int x3 = myinit(words[3]);
            if(x1 !=-1 & x2 != -1 && x3 != -1){
                scheduler();             
            }else{
                return 2;
            }
        }
    }

    return 0;
}

void help(){
   printf(""
           "COMMAND         DESCRIPTION\n"
           "help            Displays all the commands\n"
           "quit            Exits / terminates the shell with \"Bye!\"\n"
           "set VAR STRING  Assigns a value to shell memory\n"
           "print VAR       Displays the STRING assigned to VAR\n"
           "run SCRIPT.TXT  Executes the file SCRIPT.TXT\n"
           "exec prog1 prog2 prog3   Executes up to 3 concurrent programs provided as arguments\n");
}

int increment(void) 
{ 
    return x++; 
}

int interpreter(char *words[], int no_var){

    if(strcmp("exec", words[0])!=0 && strcmp("help", words[0])!=0 && strcmp("set", words[0])!=0 && strcmp("print", words[0])!=0 && strcmp("run", words[0])!=0 && strcmp("quit", words[0])!=0){
            printf("Unknown command\n");
            return 2;
        }

    if(strcmp(words[0], "help")==0){
        if(no_var !=1){
            printf("Unknown command: The syntax for help is incorrect! Should've been: help\n");
            return 2;
        }else{
            help();
        }
    }else if(strcmp(words[0], "quit")==0){
            printf("Bye!\n");
            return 3;
        
    }else if(strcmp(words[0], "set")==0){
        if(no_var!=3){
            printf("Unknown command: The syntax for set is incorrect! Should've been: set [var] [string]\n");
            return 2;
        }else{
            set(words[1], words[2]);
            increment();
        }
    }else if(strcmp(words[0], "print")==0){
        if(no_var!=2){
            printf("Unknown command: The syntax for print is incorrect! Should've been: print [var]\n");
            return 2;
        }
        else{
            print(words[1]);
        }
    }else if(strcmp(words[0], "run")==0){
        if(no_var!=2){
            printf("Unknown command: The syntax for run is incorrect! Should've been: run [file]\n");
            return 2;
        }else{
            run(words[1]);
        }
    }else if(strcmp(words[0], "exec")==0){
        if(no_var !=2 && no_var!=3 && no_var !=4){
            printf("Unkown command: The syntax for exec is incorrect: Should've been exec prog1 prog2 prog3\n");
            return 2;
        }else{
            exec(words, no_var-1);
        }
    }
    else{
        printf("Unknown command");
        return 2;
    }

    return 0;
}
