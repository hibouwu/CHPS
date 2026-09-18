all: fibotest.o
	cc -o fibotest -L/home/marek/bin/fibonacci/lib fibotest.o -lfibonacci #-Wl,-rpath,/home/marek/bin/fibonacci/lib -lfibonacci 

fibotest.o: fibotest.c
	cc -o fibotest.o -I/home/marek/bin/fibonacci/include -c fibotest.c

clean:
	rm -f fibotest fibotest.o
