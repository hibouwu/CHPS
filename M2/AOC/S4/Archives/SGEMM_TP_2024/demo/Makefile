CC=gcc
CFLAGS=-O2 -g -Wall
OPTFLAGS=-O2 -g -Wall # improve me
OBJS=kernel.o rdtsc.o driver.o

all:	bench

bench:	$(OBJS)
	$(CC) -o $@ $^

kernel.o: kernel.c
	$(CC) $(OPTFLAGS) -c $< -o $@

driver.o: driver.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) bench
