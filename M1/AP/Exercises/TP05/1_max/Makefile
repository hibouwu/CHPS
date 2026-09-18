CC=gcc
CFLAGS=-O3 -pthread

max_1: max_ref.c max_1.c
	$(CC) $(CFLAGS) -c max_ref.c
	$(CC) $(CFLAGS) -c max_1.c
	$(CC) $(CFLAGS) -o $@ max_ref.o max_1.o

max_2: max_ref.c max_2.c
	$(CC) $(CFLAGS) -c max_ref.c
	$(CC) $(CFLAGS) -c max_2.c
	$(CC) $(CFLAGS) -o $@ max_ref.o max_2.o

clean:
	rm -f *.o max_1 max_2
