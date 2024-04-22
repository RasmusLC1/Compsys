GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread -lm

all: clean main
	./main
 


main: main.c -lm #lm links to math library

clean:
	rm -rf main
