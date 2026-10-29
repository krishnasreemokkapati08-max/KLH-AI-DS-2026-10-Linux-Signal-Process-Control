#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t worker_pid = fork();

    if (worker_pid < 0) {
        perror("fork");
        return 1;
    }

    if (worker_pid == 0) {
        execl("./worker", "worker", (char *)NULL);
        perror("execl");
        _exit(1);
    }

    printf("Controller started worker PID=%ld\n", (long)worker_pid);
    printf("Commands: p = pause, r = resume, t = terminate, q = quit\n");

    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') continue;

        int sig = 0;
        if (ch == 'p') sig = SIGSTOP;
        else if (ch == 'r') sig = SIGCONT;
        else if (ch == 't' || ch == 'q') sig = SIGTERM;
        else {
            printf("Unknown command. Use p, r, t, or q.\n");
            continue;
        }

        if (kill(worker_pid, sig) == -1) {
            perror("kill");
            break;
        }

        if (ch == 'p') printf("Pause signal sent to %ld.\n", (long)worker_pid);
        else if (ch == 'r') printf("Resume signal sent to %ld.\n", (long)worker_pid);
        else {
            printf("Termination signal sent to %ld.\n", (long)worker_pid);
            break;
        }
    }

    if (waitpid(worker_pid, NULL, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    printf("Controller: worker process has finished.\n");
    return 0;
}
