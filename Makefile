CC=gcc
CFLAGS=-I. #-O2
RUNDIR=./

all: collatz_seq collatz_seq_fast

collatz_seq: collatz_seq.o
	$(CC) -o collatz_seq collatz_seq.o

collatz_seq_fast: collatz_seq_fast.o
	$(CC) -o collatz_seq_fast collatz_seq_fast.o

clean:
	rm -f *.o *.exe *.bak

test: all
	$(RUNDIR)collatz_seq 1024 100
	$(RUNDIR)collatz_seq_fast 1024 100
	$(RUNDIR)collatz_seq 1000 100
	$(RUNDIR)collatz_seq_fast 1000 100

distr: all
	tar -cvzf - ../UMANtec >../UMANtec.tgz
 