CFLAGS=-g -fsanitize=address -Wall -Wextra -pedantic

all: pointerexcercises Hexcounter hello

pointerexcercises: pointerexcercises.c
	gcc pointerexcercises.c -o pointerexcercises  $(CFLAGS)

Hexcounter: Hexcounter.c
	gcc Hexcounter.c -o Hexcounter  $(CFLAGS)

hello: hello.c
	gcc hello.c -o hello  $(CFLAGS)

clean:
	rm -f pointerexcercises