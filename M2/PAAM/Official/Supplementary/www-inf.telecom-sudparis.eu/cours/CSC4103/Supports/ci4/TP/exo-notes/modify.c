#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "student.h"

int main(int argc, char** argv) {
	if(argc != 4) {
		fprintf(stderr, "usage: %s file name rank\n", argv[0]);
		return 1;
	}
	
	FILE* f = fopen(argv[1], "r+");
	
	if(!f) {
		fprintf(stderr, "fopen %s: %s\n", argv[1], strerror(errno));
		return 1;
	}

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(struct student);
	struct student* students = malloc(n * sizeof(struct student));
	
	fseek(f, 0, SEEK_SET);
	if(fread(students, sizeof(struct student), n, f) != n) {
		fprintf(stderr, "error while reading %s: %s\n", argv[1], strerror(errno));
		return 1;
	}

	for(int i=0; i<n; i++) {
		printf("%s: %d\n", students[i].name, students[i].rank);
	}

	for(int i=0; i<n; i++) {
		if(!strcmp(students[i].name, argv[2])) {
			students[i].rank = atoi(argv[3]);
			printf("%s => %d\n", students[i].name, students[i].rank);
			fseek(f, i * sizeof(struct student), SEEK_SET);
			if(!fwrite(&students[i], sizeof(struct student), 1, f)) {
				fprintf(stderr, "error while writing %s: %s\n", argv[1], strerror(errno));
				return 1;
			}
		}
	}
	
	return 0;
}
