CC=gcc
CFLAGS=-g -masm=intel -O1

q1_dotprod: q1_dotprod.c q1_dotprod_variants.c
	$(CC) $(CFLAGS) -c q1_dotprod.c
	$(CC) $(CFLAGS) -c q1_dotprod_variants.c
	$(CC) $(CFLAGS) -o q1_dotprod q1_dotprod.o q1_dotprod_variants.o

q2_dependencies: q2_dependencies.c q2_dependencies_variants.c constants.h
	$(CC) $(CFLAGS) -c q2_dependencies.c
	$(CC) $(CFLAGS) -c q2_dependencies_variants.c
	$(CC) $(CFLAGS) -o q2_dependencies q2_dependencies.o q2_dependencies_variants.o

all: q1_dotprod q2_dependencies

clean:
	rm -f *.o q1_dotprod q2_dependencies
