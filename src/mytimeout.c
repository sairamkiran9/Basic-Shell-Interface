/**
 *@file mytimeout.c
 *@brief Kill the process if the specified time is completed
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

void handle_timeout()
{
    /**
     * method that kills the process when it's timeout
     */
    kill(pid, SIGTERM);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s snds cmd [cmd-args]\n", argv[0]);
        return 1;
    }

    int timeout = atoi(argv[1]);
    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Error: fork() failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        /**
         * call the binaries
         */
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "Error: execvp() failed.\n");
        exit(1);
    }
    else
    {
        int status;
        signal(SIGALRM, handle_timeout);
        alarm(timeout);
        /**
         * Wait for child process to terminate
         */
        if (waitpid(pid, &status, 0) < 0)
        {
            fprintf(stderr, "Error: waitpid() failed.\n");
            return 1;
        }
    }
}
