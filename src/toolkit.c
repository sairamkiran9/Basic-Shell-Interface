#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/utils.h"

// void execute_cmds1(tokenlist *args_list, tokenlist *tokens, int index, int flag)
// {
//     int pid = fork();
//     int status = 0;
//     if (pid == 0)
//     {
//         status = 1;
//         if (strcmp(tokens->items[0], "mytree.x") == 0)
//         {
//             execute_builtins(args_list, tokens, index, flag);
//         }
//         else if (strcmp(tokens->items[0], "mytime.x") == 0)
//         {
//             execute_binaries(args_list, tokens, index, flag);
//         }
//         else if (strcmp(tokens->items[0], "mymtimes.x") == 0)
//         {
//             execute_binaries(args_list, tokens, index, flag);
//         }
//         else
//         {
//             execute_builtins(args_list, tokens, index, flag);
//         }
//         exit(0);
//     }
//     else
//     {
//         waitpid(pid, &status, 0);
//     }
// }

void execute_cmds(tokenlist *args_list)
{
    int i, flag = 0;
    tokenlist *tokens = new_tokenlist();
    for (i = 0; i < args_list->size; i++)
    {
        if ((strcmp(args_list->items[i], ">") == 0) || (strcmp(args_list->items[i], "<") == 0))
        {
            flag = 1;
            break;
        }
        add_token(tokens, args_list->items[i]);
    }
    if (tokens->size == 0)
    {
        return;
    }
    if ((strcmp(tokens->items[0], "exit") == 0) || (strcmp(tokens->items[0], "myexit") == 0))
    {
        exit(0);
    }
    else if (strcmp(tokens->items[0], "mypwd") == 0)
    {
        get_mypwd();
    }
    else if (strcmp(tokens->items[0], "mycd") == 0)
    {
        execute_mycd(tokens);
    }
    else
    {
        int pid = fork();
        int status = 0;
        if (pid == 0)
        {
            status = 1;
            execute_builtins(args_list, tokens, i, flag);
            exit(0);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
}