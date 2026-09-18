CC=gcc
CFLAGS=-O3 -pthread

gemmtrace_1: gemmtrace_ref.c gemmtrace_1.c
	$(CC) $(CFLAGS) -c gemmtrace_ref.c
	$(CC) $(CFLAGS) -c gemmtrace_1.c
	$(CC) $(CFLAGS) -o $@ gemmtrace_ref.o gemmtrace_1.o

gemmtrace_2: gemmtrace_ref.c gemmtrace_2.c
	$(CC) $(CFLAGS) -c gemmtrace_ref.c
	$(CC) $(CFLAGS) -c gemmtrace_2.c
	$(CC) $(CFLAGS) -o $@ gemmtrace_ref.o gemmtrace_2.o

clean:
	rm -f *.o gemmtrace_1 gemmtrace_2
