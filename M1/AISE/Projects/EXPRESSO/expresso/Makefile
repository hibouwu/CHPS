PREFIX ?= /usr/local
CC = gcc
CFLAGS = -Wall -g -std=c99 -fPIC
LDLIBS = -lpthread

# List any additional object files below. 'make' will compile the corresponding
# sources automatically.
# For example: add 'my_other_code.o', if you need to compile 'my_other_code.c'
OBJECTS := expresso.o

all: $(OBJECTS)
	$(CC) -o libexpresso.so $(CFLAGS) -shared $^
	ar rcs libexpresso.a $^

$(OBJECTS): $(wildcard *.h)

clean:
	rm -f *.o libexpresso.*
	$(MAKE) -C tests clean

test:
	$(MAKE) -C tests run

install: all
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	cp expresso.h $(PREFIX)/include/
	cp libexpresso.* $(PREFIX)/lib/

uninstall:
	rm -f $(PREFIX)/include/expresso.h
	rm -f $(PREFIX)/lib/libexpresso.*
