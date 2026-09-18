PREFIX ?= /usr/local

all: static shared

install: static shared
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	cp fibonacci.h $(PREFIX)/include/
	cp libfibonacci.* $(PREFIX)/lib/

shared: fibonacci.o
	cc -o libfibonacci.so -shared -fPIC fibonacci.o

static: fibonacci.o
	ar rcs libfibonacci.a fibonacci.o

fibonacci.o: fibonacci.c fibonacci.h
	cc -o fibonacci.o -c fibonacci.c

clean:
	rm -rf fibonacci.o libfibonacci.*

uninstall:
	rm -f $(PREFIX)/include/fibonacci.h
	rm -f $(PREFIX)/lib/libfibonacci.*
