// Saad Shahbaz, McGill ID: 260845253
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include "shellmemory.h"
#include "interpreter.h"

int parse(char *str) //set x lolz
{

    if(*str == '\n'){
        return -1;
    }
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;  //            my name is ibrahim
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }


    char **ret_arr = (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return -1;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    int count = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            count = count+1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }
    return interpreter(ret_arr, count);
}

int shellUI(){
    printf("Kernel 1.0 loaded!\n");
    printf("Welcome to the Saad Shahbaz shell!\n");
    printf("Version 2.0 Created Feburary 2020\n");
    while(1) {
        char input[1000];
        int wstatus;

        int errorcode = 0;

        // prompt
        printf("$ ");
        fgets(input, 999, stdin);

        errorcode = parse(input);

        if(errorcode == -1 || errorcode == 2){
            continue;
        }else if(errorcode == 3){
            break;
        }
    }

    return 0;
}