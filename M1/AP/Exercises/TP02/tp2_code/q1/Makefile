CC=gcc
CFLAGS=-g -O1
CFLAGS_INTEL= $(CFLAGS) -masm=intel


loop: main.c asm.c
	$(CC) $(CFLAGS_INTEL) -c main.c
	$(CC) $(CFLAGS_INTEL) -c asm.c
	$(CC) -o $@ main.o asm.o

ALL=loop 

clean:
	rm -f *.o $(ALL)
