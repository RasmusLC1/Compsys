GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread -lm

all: clean main
	./main > output.txt
 


main: main.c pipeline.o -lm #lm links to math library

pipeline.o: pipeline.c pipeline.h
	$(GCC) -c $< -o $@


clean:
	rm -rf main
