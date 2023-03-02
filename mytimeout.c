#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s snds cmd [cmd-args]\n", argv[0]);
        return 1;
    }

    int timeout = atoi(argv[1]);
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Error: fork() failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        execvp(argv[2], &argv[2]);
        printf("Error: execvp() failed.\n");
        exit(1);
    }
    else
    {
        // Parent process
        int status;
        int ret = 0;

        // Set up alarm signal for timeout
        alarm(timeout);

        // Wait for child process to finish or receive signal
        if (waitpid(pid, &status, 0) < 0)
        {
            printf("Error: waitpid() failed.\n");
            return 1;
        }

        // Check if child process was terminated by signal
        if (WIFSIGNALED(status))
        {
            printf("Process terminated by signal %d.\n", WTERMSIG(status));
            ret = 1;
        }

        return ret;
    }
}
