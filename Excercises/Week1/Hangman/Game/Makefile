CC=gcc
CFLAGS= -Wall -Werror -Wextra -pedantic

all: main

main: TextfileReader.o Functions.o
	$(CC) TextfileReader.o Functions.o -o main $(CFLAGS)

TextfileReader.o: TextfileReader.c
	$(CC) -c TextfileReader.c $(CFLAGS)

Functions.o: Functions.c
	$(CC) -c Functions.c $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

do_main: main
	./main

clean:
	rm -f fib.o main.o main