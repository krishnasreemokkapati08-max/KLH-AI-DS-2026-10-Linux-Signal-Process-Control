
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define FIFO_AB "/tmp/ipc_chat_ab"
#define FIFO_BA "/tmp/ipc_chat_ba"
#define MSG_SIZE 512

volatile sig_atomic_t running = 1;

void handle_signal(int sig)
{
    (void)sig;
    running = 0;
}

void get_timestamp(char *buf, size_t size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (t != NULL)
        strftime(buf, size, "%H:%M:%S", t);
    else
        snprintf(buf, size, "--:--:--");
}

void receive_messages(int fd, const char *peer)
{
    char buffer[MSG_SIZE];
    char line[MSG_SIZE];
    size_t used = 0;

    while (running)
    {
        ssize_t n = read(fd, buffer, sizeof(buffer));

        if (n > 0)
        {
            for (ssize_t i = 0; i < n; i++)
            {
                if (buffer[i] == '\n' || used == sizeof(line) - 1)
                {
                    line[used] = '\0';

                    if (used > 0)
                    {
                        char timestamp[16];
                        get_timestamp(timestamp, sizeof(timestamp));

                        printf("\n[%s] User %s: %s\n> ",
                               timestamp, peer, line);
                        fflush(stdout);
                    }

                    used = 0;
                }
                else
                {
                    line[used++] = buffer[i];
                }
            }
        }
        else if (n == 0)
        {
            break;
        }
        else if (errno != EINTR)
        {
            perror("read");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 ||
        (strcmp(argv[1], "A") != 0 &&
         strcmp(argv[1], "B") != 0))
    {
        fprintf(stderr, "Usage: %s A|B\n", argv[0]);
        return 1;
    }

    const char *me = argv[1];
    const char *peer = strcmp(me, "A") == 0 ? "B" : "A";

    const char *out_path =
        strcmp(me, "A") == 0 ? FIFO_AB : FIFO_BA;

    const char *in_path =
        strcmp(me, "A") == 0 ? FIFO_BA : FIFO_AB;

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGPIPE, SIG_IGN);

    if (mkfifo(FIFO_AB, 0600) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        return 1;
    }

    if (mkfifo(FIFO_BA, 0600) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        return 1;
    }

    printf("\n====================================\n");
    printf("       IPC CHAT - USER %s\n", me);
    printf("====================================\n");
    printf("Waiting for User %s...\n", peer);
    fflush(stdout);

    int out_fd = open(out_path, O_WRONLY);

    if (out_fd == -1)
    {
        perror("open output FIFO");
        return 1;
    }

    int in_fd = open(in_path, O_RDONLY);

    if (in_fd == -1)
    {
        perror("open input FIFO");
        close(out_fd);
        return 1;
    }

    printf("\nConnected! Chat started.\n");
    printf("Type /quit to exit.\n\n> ");
    fflush(stdout);

    pid_t receiver = fork();

    if (receiver == -1)
    {
        perror("fork");
        close(in_fd);
        close(out_fd);
        return 1;
    }

    if (receiver == 0)
    {
        close(out_fd);
        receive_messages(in_fd, peer);
        close(in_fd);
        _exit(0);
    }

    close(in_fd);

    char *line = NULL;
    size_t capacity = 0;

    while (running)
    {
        ssize_t length = getline(&line, &capacity, stdin);

        if (length == -1)
            break;

        if (strcmp(line, "/quit\n") == 0 ||
            strcmp(line, "/quit") == 0)
        {
            break;
        }

        if (length == 1 && line[0] == '\n')
            continue;

        size_t sent = 0;

        while (sent < (size_t)length && running)
        {
            ssize_t n = write(out_fd, line + sent,
                              (size_t)length - sent);

            if (n > 0)
            {
                sent += (size_t)n;
            }
            else if (n < 0 && errno == EINTR)
            {
                continue;
            }
            else
            {
                perror("write");
                running = 0;
                break;
            }
        }

        printf("> ");
        fflush(stdout);
    }

    running = 0;
    free(line);
    close(out_fd);

    kill(receiver, SIGTERM);
    waitpid(receiver, NULL, 0);

    printf("\nUser %s disconnected.\n", me);

    return 0;
}
