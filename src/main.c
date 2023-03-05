#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"

FILE *fd;
char buf[82];

int main()
{
    int pipe_count = 0;

    init_path();

    if ((fd = fopen("/dev/tty", "r+")) == 0)
    {
        perror("Cannot open /dev/tty\n");
        exit(0);
    }

    while (1)
    {
        printf("$ ");
        if (fgets(buf, 82, fd) == NULL)
        {
            exit(0);
        }

        tokenlist *tokens = get_tokens(buf, "|");
        tokenlist *args_list[tokens->size];

        for (int i = 0; i < tokens->size; i++)
        {
            args_list[i] = get_tokens(tokens->items[i], " ");
        }

        pipe_count = tokens->size - 1;
        if (pipe_count == 0)
        {
            execute_cmds(args_list[0]);
        }
        else if (pipe_count >= 1)
        {
            execute_pipe(args_list, pipe_count);
        }
        else
        {
            continue;
        }
    }
}