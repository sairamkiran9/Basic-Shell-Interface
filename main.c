#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

FILE *fd;
char buf[82];


int main()
{
    int pipe_count = 0;

    binaries_path = getenv("PWD");
    printf("%s\n", binaries_path);

    if ((fd = fopen("/dev/tty", "r+")) == 0)
    {
        perror("Cannot open /dev/tty\n");
        exit(0);
    }

    while (1)
    {
        printf("$ ");
        fgets(buf, 82, fd);

        // printf("%s", buf);

        tokenlist *tokens = get_tokens(buf, "|");
        // print_tokens(tokens);

        tokenlist *args_list[tokens->size];

        for (int i = 0; i < tokens->size; i++)
        {
            args_list[i] = get_tokens(tokens->items[i], " ");
            // print_tokens(args_list[i]);
        }

        pipe_count = tokens->size;
        if (pipe_count == 1)
        {
            execute_cmds(args_list[0]);
        }
        else if (pipe_count >= 2){
            execute_pipe(args_list);    
        }
        else {
            continue;
        }
    }
}