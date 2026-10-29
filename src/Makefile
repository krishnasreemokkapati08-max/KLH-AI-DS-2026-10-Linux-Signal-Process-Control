CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src

all: worker controller

worker: $(SRC)/worker.c
	$(CC) $(CFLAGS) $(SRC)/worker.c -o worker

controller: $(SRC)/controller.c
	$(CC) $(CFLAGS) $(SRC)/controller.c -o controller

clean:
	rm -f worker controller
