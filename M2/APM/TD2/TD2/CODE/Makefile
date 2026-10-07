CC=gcc
CFLAGS=-O3 -Wall
EXE1=pi.exe

all : $(EXE1) $(EXE2)

$(EXE1) : pi.o
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f *.o $(EXE1) $(EXE2)

proper :
	rm -f *.o
