# TP Floyd-Warshall : code de base (CPU)
CC    ?= gcc
FLAGS := -O3 -Wall

fw: fw.c fw_utils.h
	$(CC) $(FLAGS) -o $@ fw.c

run: fw
	./fw -n 512

clean:
	rm -f fw

.PHONY: run clean
