CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=gnu99 -pthread
#fibs fauxgrep fauxgrep-mt fhistogram fhistogram-mt
EXAMPLES= fibs
SHELL := /bin/bash
CLEANALL = fibs fauxgrep fauxgrep-mt fhistogram fhistogram-mt

LOOPS = 100000
ACTIVETEST = ./fibs -n 4 < fibtest.txt
.PHONY: all loop start end test clean ../src.zip

# ./fauxgrep logic Breakout
# ./fauxgrep-mt logic Breakout -n 4
# ./fibs -n 4 < fibtest.txt
# ./fhistogram-mt logic Breakout -n 4
# ./fhistogram logic Breakout
# valgrind --tool=memcheck ./fibs -n 4 < fibtest.txt


all: clean start $(TESTS) $(EXAMPLES) loop  end

ifdef LOOPS
loop: 
	date +%s > totaltime.txt
	for ((i=1; i <= ${LOOPS}; ++i)) do ${ACTIVETEST}; done
	date +%s >> totaltime.txt
	
endif	

job_queue.o: job_queue.c job_queue.h
	$(CC) -c job_queue.c $(CFLAGS)

%: %.c job_queue.o
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TESTS)
	@set e; for test in $(TESTS); do echo ./$$test; ./$$test; done

clean:
	rm -rf $(CLEANALL) $(EXAMPLES) *.o core

../src.zip:
	make clean
	cd .. && zip src.zip -r src
