
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    (void)sig;
    running = 0;
}

int main(void) {
    struct sigaction action;
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Worker started. PID=%ld\n", (long)getpid());

    int count = 0;
    while (running) {
        printf("PID %ld: working... %d\n",
               (long)getpid(), ++count);
        sleep(2);
    }

    printf("Worker exiting safely.\n");
    return 0;
}

