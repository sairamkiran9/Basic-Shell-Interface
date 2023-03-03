#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "utils.h"

void execute_cmds(tokenlist *tokens)
{
    if (tokens->size == 0)
    {
        return;
    }
    if ((strcmp(tokens->items[0], "exit") == 0) || (strcmp(tokens->items[0], "myexit") == 0))
    {
        exit(0);
    }
    else if (strcmp(tokens->items[0], "mytree.x") == 0)
    {
        execute_binaries(tokens);
    }
    else if (strcmp(tokens->items[0], "mytime.x") == 0)
    {
        execute_binaries(tokens);
    }
    else if (strcmp(tokens->items[0], "mymtimes.x") == 0)
    {
        execute_binaries(tokens);
    }
    else if (strcmp(tokens->items[0], "mytimeout.x") == 0)
    {
        execute_binaries(tokens);
    }
    else if (strcmp(tokens->items[0], "mytoolkit.x") == 0)
    {
        execute_binaries(tokens);
    }
    else if (strcmp(tokens->items[0], "mycd") == 0)
    {
        execute_mycd(tokens);
    }
    else if (strcmp(tokens->items[0], "mypwd") == 0)
    {
        get_mypwd();
    }
    else
    {
        execute_builtins(tokens);
    }
}