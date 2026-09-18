CC=gcc
CFLAGS=-g -masm=intel -O3 -fPIC

gather: gather.c gather_asm.c
	$(CC) $(CFLAGS) -c gather.c
	$(CC) $(CFLAGS) -c gather_asm.c
	$(CC) $(CFLAGS) -o $@ gather.o gather_asm.o

transpose: transpose.c transpose_asm.c
	$(CC) $(CFLAGS) -c transpose.c
	$(CC) $(CFLAGS) -c transpose_asm.c
	$(CC) $(CFLAGS) -o $@ transpose.o transpose_asm.o

clean:
	rm -f *.o gather transpose
