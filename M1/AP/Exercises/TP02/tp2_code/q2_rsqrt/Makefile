CC=gcc
CFLAGS=-g -masm=intel -flto -O0

driver: driver.c benchmarks.c variants.c
	$(CC) $(CFLAGS) -lm -c benchmarks.c
	$(CC) $(CFLAGS) -c driver.c
	$(CC) $(CFLAGS) -c variants.c
	$(CC) $(CFLAGS) -lm -o $@ benchmarks.o driver.o variants.o

clean:
	rm -f *.o driver
