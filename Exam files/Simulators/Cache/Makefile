GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread -lm

all: clean main
	./main
 


main: main.c cache.o -lm #lm links to math library

cache.o: cache.c cache.h
	$(GCC) -c $< -o $@

clean:
	rm -rf main
