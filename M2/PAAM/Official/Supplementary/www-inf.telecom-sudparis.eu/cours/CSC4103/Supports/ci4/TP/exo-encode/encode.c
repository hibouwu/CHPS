#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define N 256

void encode(char key, FILE* in, FILE* out) {
	char buf[N];
	int i, n;
	
	while((n = fread(buf, 1, N, in))) {
		for(i=0; i<n; i++)
			buf[i] = buf[i] ^ key;

		if(!fwrite(buf, 1, n, out)) {
			fprintf(stderr, "fwrite: %s\n", strerror(errno));
			return;
		}
	}
	
	/* we cannot directly know if n = 0 because of an error */
	if(feof(in))
		return;
	else {
		fprintf(stderr, "fread: %s\n", strerror(errno));
		return;
	}
}

int main(int argc, char** argv) {
	FILE* in;
	FILE *out;
	
	if(argc != 4) {
		fprintf(stderr, "Usage: %s key in out\n", argv[0]);
		return 1;
	}

	char key = atoi(argv[1]);
	fprintf(stderr, "encode %s with the key %d to %s\n", argv[2], key, argv[3]);
	
	if(strcmp(argv[2], "-"))
		in = fopen(argv[2], "r");
	else
		in = stdin;

	if(!in) {
		fprintf(stderr , "fopen %s: %s\n", argv[2], strerror(errno));
		return 2;
	}

	if(strcmp(argv[3], "-"))
		out = fopen(argv[3], "w+");
	else
		out = stdout;

	if(!out) {
		fprintf(stderr , "fopen %s: %s\n", argv[3], strerror(errno));
		return 2;
	}

	encode(key, in, out);

	fclose(out);
	fclose(in);
	
	return 0;
}
