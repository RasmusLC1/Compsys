GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread -lm

all: clean min_cache_sim
	./min_cache_sim 4 128 16
 

valgrindtest: clean min_cache_sim
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./min_cache_sim 4 128 16

test: clean unittest
	./unittest > log.txt


rebuild: clean all

memory.o: memory.c memory.h
	$(GCC) -c $< -o $@

cache.o: cache.c cache.h
	$(GCC) -c $< -o $@

min_cache_sim: min_cache_sim.c memory.o cache.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS) -g

#unittest
minunit.o: minunit.c minunit.h
	$(GCC) -c $< -o $@

unittest: minunit.c memory.o cache.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS) -g

zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o min_cache_sim memory minunit cache vgcore*
