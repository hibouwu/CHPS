CC = gcc
CFLAGS = -Wall -g -std=c99 -I..
LDFLAGS = -L..
LDLIBS = -l:libexpresso.a

# Add any additional test executables below. 'make' will compile them
# automatically.
# For example: add 'my_new_test', if you want 'make' to compile 'my_new_test.c'
TESTS = add-to-all add-to-all-twice basic-sum basic-sum-two-waits no-tasks

all: $(TESTS)

run: all
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
