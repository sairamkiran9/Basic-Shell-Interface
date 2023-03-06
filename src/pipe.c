/**
 * @file pipe.c
 * @brief Method to support single and multi pipe functionalty
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/utils.h"

void execute_single_pipe(tokenlist *cmd1, tokenlist *cmd2)
{
    /**
     * single pipe
     */

    /* file descriptor array for piping */
    int p_fds[2];
    if (pipe(p_fds) == -1)
    {
        perror("pipe");
        exit(0);
    }
    /* child process 1 */
    int pid1 = fork();
    int status1 = 0;
    if (pid1 == 0)
    {
        close(p_fds[0]);
        /* output redirection */
        dup2(p_fds[1], 1);
        /* execute commands for 1st args set */
        execute_cmds(cmd1);
        status1 = 1;
        exit(1);
    }
    /* child process 2 */
    int pid2 = fork();
    int status2 = 0;
    if (pid2 == 0)
    {
        close(p_fds[1]);
        /* input redirection */
        dup2(p_fds[0], 0);
        /* execute commands for 2st args set */
        execute_cmds(cmd2);
        status2 = 1;
        exit(1);
    }
    close(p_fds[0]);
    close(p_fds[1]);
    /* wait for child process 1 to complete */
    waitpid(pid1, &status1, 0);
    /* wait for child process 2 to complete */
    waitpid(pid2, &status2, 0);
}

void execute_multi_pipe(tokenlist *args_list[], int pipe_count, int curr_pipe)
{
    /**
     * recursive method to support infinite piping
     */
    if (curr_pipe < pipe_count - 1)
    {
        /* file descriptor array for piping */
        int p_fds[2];
        if (pipe(p_fds) == -1)
        {
            perror("pipe ");
            exit(0);
        }
        /* child process 1 */
        int pid1 = fork();
        int status1 = 0;
        if (pid1 == 0)
        {
            close(p_fds[0]);
            /* output redirection */
            dup2(p_fds[1], 1);
            /* execute commands for 1st args set */
            execute_cmds(args_list[curr_pipe]);
            status1 = 1;
            exit(1);
        }
        /* child process 2 */
        int pid2 = fork();
        int status2 = 0;
        if (pid2 == 0)
        {
            close(p_fds[1]);
            /* input redirection */
            dup2(p_fds[0], 0);
            /* recursive call for next pipe execution */
            execute_multi_pipe(args_list, pipe_count, curr_pipe + 1);
            status2 = 1;
            exit(1);
        }
        close(p_fds[0]);
        close(p_fds[1]);
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
    }
    else
    {
        /* For the last pipe */
        execute_single_pipe(args_list[curr_pipe], args_list[curr_pipe + 1]);
    }
}

int execute_pipe(tokenlist *tokens[], int pipe_count)
{
    /**
     * redirect based on number of pipes
     */
    if (pipe_count == 1)
    {
        /* single pipe */
        execute_single_pipe(tokens[0], tokens[1]);
    }
    else if (pipe_count >= 2)
    {
        /* multi pipe */
        execute_multi_pipe(tokens, pipe_count, 0);
    }
    return 0;
}