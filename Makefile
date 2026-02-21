$CFLAGS=-Wall -Wextra -std=23 -pedantic -ggdb

program: main.c
	$(CC) $(CFLAGS) -o main main.c -lraylib
