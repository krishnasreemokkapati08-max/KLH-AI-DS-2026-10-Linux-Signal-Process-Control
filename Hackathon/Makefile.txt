
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = chat
SOURCE = chat.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
