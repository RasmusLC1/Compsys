CC = gcc
CFLAGS =-Wall -Wextra -pedantic -std=gnu11
LD_FLAGS = -lpthread

all : clean fork15 fork23 threading17
	./threading17

rebuild : clean all

csapp.o : csapp.c csapp.h
	$(CC) $(CFLAGS) -c $< -o $@

fork15 : fork15.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)

fork23 : fork23.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)

threading17 : threading17.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)


clean :
	rm -rf *.o fork
