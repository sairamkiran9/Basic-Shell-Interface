#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

void handle_timeout() {
    /* Handle timeout */
    kill(pid, SIGTERM);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s snds cmd [cmd-args]\n", argv[0]);
        return 1;
    }

    int timeout = atoi(argv[1]);
    pid = fork();

    if (pid < 0)
    {
        printf("Error: fork() failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        execvp(argv[2], &argv[2]);
        printf("Error: execvp() failed.\n");
        exit(1);
    }
    else
    {
        int status;
        signal(SIGALRM, handle_timeout);
        alarm(timeout);

        if (waitpid(pid, &status, 0) < 0)
        {
            printf("Error: waitpid() failed.\n");
            return 1;
        }
    }
}
