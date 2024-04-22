CFLAGS=-Wall -Wextra -pedantic -g
CC=gcc


run: clean test
	./test

test: program.o Exec.o Fork.o 
	$(CC) program.o Exec.o Fork.o  -o test $(CFLAGS)

program.o: program.c
	$(CC) -c program.c $(CFLAGS)

Exec.o: Exec.c
	$(CC) -c Exec.c $(CFLAGS)

Fork.o: Fork.c
	$(CC) -c Fork.c $(CFLAGS)

clean:
	rm -rf test *.o