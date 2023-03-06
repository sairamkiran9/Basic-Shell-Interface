/**
 * @file toolkit.c
 * @brief This file intializes the toolkit, it fetches the input and
 * calls the respective methods.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/utils.h"

void init_toolkit()
{
    /* This method runs until the user interupts or exit. */
    int pipe_count = 0;
    while (1)
    {
        printf("$ ");
        if (fgets(buf, 82, stdin) == NULL)
        {
            exit(0);
        }

        /* parse input into tokens based on pipe */
        tokenlist *tokens = get_tokens(buf, "|");
        tokenlist *args_list[tokens->size];

        for (int i = 0; i < tokens->size; i++)
        {
            args_list[i] = get_tokens(tokens->items[i], " ");
        }

        pipe_count = tokens->size - 1;
        if (pipe_count == 0)
        {
            /* no pipe in the input */
            execute_cmds(args_list[0]);
        }
        else if (pipe_count >= 1)
        {
            /* one or more pipes in the input */
            execute_pipe(args_list, pipe_count);
        }
        else
        {
            /* provided input is empyt */
            continue;
        }
        clean_mem(tokens, args_list);
    }
}

void execute_cmds(tokenlist *args_list)
{
    /* This menthod redirects the input arguments and also check for ioredirection */
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
        free(tokens);
        exit(0);
    }
    else if ((flag == 0) && (strcmp(tokens->items[0], "mypwd") == 0))
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
        if (pid < 0)
        {
            fprintf(stderr, "Error: fork() failed.\n");
            exit(0);
        }
        else if (pid == 0)
        {
            status = 1;
            if (strcmp(tokens->items[0], "mypwd") == 0)
            {
                /* Check for io redirection */
                check_fileio(args_list, tokens, i, flag);
                get_mypwd();
            }
            else
            {
                /* execute shell methods */
                execute_builtins(args_list, tokens, i, flag);
            }
            exit(0);
        }
        else
        {
            /* wait for child process to complete */
            waitpid(pid, &status, 0);
        }
    }
    free(tokens);
}