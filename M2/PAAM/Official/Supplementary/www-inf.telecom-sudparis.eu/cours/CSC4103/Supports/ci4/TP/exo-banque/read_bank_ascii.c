#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {

  FILE*f = fopen(argv[1], "r");
  int val;
  int ret;
  do {
    ret = fscanf(f, "%d", &val);
    if(ret == EOF || ret == 0)
      break;
    printf("read: %x / %d\n", val, val);
  } while(1);

  fclose(f);
  return EXIT_SUCCESS;
}
