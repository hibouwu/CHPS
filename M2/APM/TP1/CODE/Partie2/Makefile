CC=gcc
CFLAGS=-O3 -Wall
EXE=mult.exe

all : $(EXE)

$(EXE) : dgemm.o
	$(CC) $(CFLAGS) -o $@ $< 

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run : mult.exe
	./$< 1000

proper : 
	rm -f *.o

clean :
	rm -f *.o $(EXE)
