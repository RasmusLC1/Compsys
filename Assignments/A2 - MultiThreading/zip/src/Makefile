CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=gnu99 -pthread

CURRENTTEST = fhistogram-mt fibs fauxgrep-mt 
TEXTFILES= TextfileComparator TextfileCleaner
ALL = fibs fauxgrep fauxgrep-mt fhistogram fhistogram-mt TextfileComparator TextfileCleaner

# Shell to allow us to registrer time
SHELL := /bin/bash


# Amount of iterations for our forloop
LOOPS = 100


CLEANER = ./TextfileCleaner


# commands to run our various programs
FAUXMT = ./fauxgrep-mt -n 4 logic Breakout
FIB = ./fibs -n 4 < fibtest.txt
HISTOMT = ./fhistogram-mt -n 4 Breakout 


FAUX = ./fauxgrep logic Breakout
HISTO = ./fhistogram Breakout


COMPARATOR = ./TextfileComparator



.PHONY: all loop test clean ../src.zip



all: clean $(TESTS) $(ALL)
	./fauxgrep-mt -n 4 logic Breakout

# Our test function which allows us to run specific files
filetest: clean $(TESTS) $(TEXTFILES) $(CURRENTTEST) looptime

ifdef LOOPS

# for loop which registrers and pipes the start and end time for
# loop completion into a txt file. There is also a loop which
# runs the code LOOPS times
looptime: 
	date +%s > totaltime.txt
	for ((i=1; i <= ${LOOPS}; ++i)) do ${FAUXMT} ; done
	date +%s >> totaltime.txt
endif	


job_queue.o: job_queue.c job_queue.h
	$(CC) -c job_queue.c $(CFLAGS)


%: %.c job_queue.o
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TESTS)
	@set e; for test in $(TESTS); do echo ./$$test; ./$$test; done

clean:
	rm -rf $(ALL) $(EXAMPLES) *.o core

../src.zip:
	make clean
	cd .. && zip src.zip -r src

# Function to pipe our results into a txt file and compare it to a known
# output
looptxt: 
	${CLEANER}
	for ((i=1; i <= ${LOOPS}; ++i)) do ${HISTOMT} >logFaux.txt &\
	${HISTOMT} >loghist.txt & ${FIB} >logFib.txt & ${COMPARATOR} ; done
