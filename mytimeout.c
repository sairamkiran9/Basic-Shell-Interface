#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s snds cmd [cmd-args]\n", argv[0]);
        exit(1);
    }

    int snds = atoi(argv[1]);
    char *cmd = argv[2];

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execvp(cmd, &argv[2]);
        perror("execvp");
        exit(1);
    } else {
        // Parent process
        signal(SIGALRM, SIG_IGN); // Ignore SIGALRM initially

        alarm(snds); // Set an alarm to send a SIGALRM signal after snds seconds

        int status;
        pid_t result = waitpid(pid, &status, 0); // Wait for the child process to finish

        if (result == -1) {
            perror("waitpid");
            exit(1);
        } else if (WIFEXITED(status)) {
            // Child process exited normally before the alarm went off
            alarm(0); // Cancel the alarm
            exit(WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            // Child process was terminated by a signal
            if (WTERMSIG(status) == SIGALRM) {
                // Alarm went off, send SIGTERM to child process
                kill(pid, SIGTERM);
            }
            // Wait for child process to exit
            waitpid(pid, &status, 0);
            exit(1);
        }
    }
}
