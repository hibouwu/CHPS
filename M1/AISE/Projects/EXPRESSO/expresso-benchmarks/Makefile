PREFIX ?= /usr/local
CC = gcc
CFLAGS = -Wall -g -O0 -std=c99 -I$(PREFIX)/include
LDFLAGS = -L$(PREFIX)/lib
LDLIBS = -lexpresso -Wl,-rpath,$(PREFIX)/lib

TESTS = dot list matmul vecmul

all: $(TESTS)

test: all
	for t in $(TESTS); \
	do \
		for w in 1 2 4 8; \
		do \
			for p in "dynamic" "static" "balanced"; \
			do \
				EXPRESSO_WORKER_COUNT=$$w EXPRESSO_SCHEDULE=$$p ./$$t ; \
			done ; \
			EXPRESSO_WORKER_COUNT=$$w ./$$t ; \
		done ; \
		./$$t ; \
	done

clean:
	rm -f $(TESTS)
