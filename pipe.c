#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "utils.h"

void execute_single_pipe(tokenlist *cmd1, tokenlist *cmd2)
{
    int p_fds[2]; // file descriptor array for piping
    if (pipe(p_fds) == -1)
    {
        perror("pipe");
        exit(0);
    }
    int pid1 = fork(); // child process 1
    int status1 = 0;
    if (pid1 == 0)
    {
        close(p_fds[0]);
        dup2(p_fds[1], 1);  // output redirection
        execute_cmds(cmd1); // execute commands for 1st args set
        status1 = 1;
        exit(1);
    }
    int pid2 = fork(); // child process 2
    int status2 = 0;
    if (pid2 == 0)
    {
        close(p_fds[1]);
        dup2(p_fds[0], 0);  // input redirection
        execute_cmds(cmd2); // execute commands for 1st args set
        status2 = 1;
        exit(1);
    }
    close(p_fds[0]);
    close(p_fds[1]);
    waitpid(pid1, &status1, 0); // wait for child process 1 to complete
    waitpid(pid2, &status2, 0); // wait for child process 1 to complete
}

void execute_multi_pipe(tokenlist *args_list[], int pipe_count, int curr_pipe)
{
    if (curr_pipe < pipe_count - 1)
    {
        int p_fds[2]; // file descriptor array for piping
        if (pipe(p_fds) == -1)
        {
            perror("pipe ");
            exit(0);
        }
        int pid1 = fork(); // child process 1
        int status1 = 0;
        if (pid1 == 0)
        {
            close(p_fds[0]);
            dup2(p_fds[1], 1);                  // output redirection
            execute_cmds(args_list[curr_pipe]); // execute commands for 1st args set
            status1 = 1;
            exit(1);
        }
        int pid2 = fork(); // child process 2
        int status2 = 0;
        if (pid2 == 0)
        {
            close(p_fds[1]);
            dup2(p_fds[0], 0);                                        // input redirection
            execute_multi_pipe(args_list, pipe_count, curr_pipe + 1); // recursive call
            status2 = 1;
            exit(1);
        }
        close(p_fds[0]);
        close(p_fds[1]);
        waitpid(pid1, &status1, 0); // wait for child process 1 to complete
        waitpid(pid2, &status2, 0); // wait for child process 2 to complete
    }
    else
    {
        execute_single_pipe(args_list[curr_pipe], args_list[curr_pipe + 1]); // For the last pipe
    }
}

int execute_pipe(tokenlist *tokens[], int pipe_count)
{
    if (pipe_count == 1)
    {
        execute_single_pipe(tokens[0], tokens[1]);
    }
    else if (pipe_count >= 2)
    {
        execute_multi_pipe(tokens, pipe_count, 0);
    }
    return 0;
}