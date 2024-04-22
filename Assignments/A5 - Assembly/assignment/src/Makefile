GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread -lm

all: clean main
	./main ../tests/hello.dis - log

test: clean unittest
	./unittest



rebuild: clean all

memory.o: memory.c memory.h
	$(GCC) -c $< -o $@

Decoder.o: Decoder.c Decoder.h
	$(GCC) -c $< -o $@

minunit.o: minunit.c minunit.h
	$(GCC) -c $< -o $@

read_exec.o: read_exec.c read_exec.h
	$(GCC) -c $< -o $@

assembly.o : assembly.c assembly.h
	$(CC) $(CFLAGS) -c $< -o $@

simulate.o : simulate.c simulate.h
	$(CC) $(CFLAGS) -c $< -o $@

unittest: minunit.c Decoder.o memory.o read_exec.o assembly.o simulate.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS) -g

main: main.c Decoder.o memory.o read_exec.o assembly.o simulate.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS) -g

zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o main minunit memory read_exec assembly simulate Decoder vgcore*
