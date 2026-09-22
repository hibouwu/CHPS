#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "student.h"

int main(int argc, char** argv) {
	if(argc != 4) {
		fprintf(stderr, "usage: %s in out rank\n", argv[0]);
		return 1;
	}

	int rank = atoi(argv[3]);
	FILE* in = fopen(argv[1], "r");

	if(!in) {
		fprintf(stderr, "fopen %s: %s\n", argv[1], strerror(errno));
		return 1;
	}

	FILE* out = fopen(argv[2], "w+");

	if(!out) {
		fprintf(stderr , "fopen %s: %s\n", argv[2], strerror(errno));
		return 1;
	}
	
	struct student s;
	
	while(fgets(s.name, N, in)) {
		s.name[strlen(s.name) - 1] = 0;
		s.rank = rank;
		if(!fwrite(&s, sizeof(struct student), 1, out)) {
			fprintf(stderr, "error while writing %s: %s\n", argv[2], strerror(errno));
			return 1;
		}
	}

	if(!feof(in)) {
		fprintf(stderr, "error while reading %s: %s\n", argv[1], strerror(errno));
		return 1;
	}
	
	return 0;
}
