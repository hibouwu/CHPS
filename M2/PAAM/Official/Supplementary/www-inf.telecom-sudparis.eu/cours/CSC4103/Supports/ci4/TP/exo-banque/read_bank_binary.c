#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {

  FILE*f = fopen(argv[1], "r");
  int val;
  while(fread(&val, sizeof(int), 1, f)) {
    printf("read: %x / %d\n", val, val);
  }

  fclose(f);
  return EXIT_SUCCESS;
}
