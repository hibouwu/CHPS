#include <stdio.h>
#include <stdlib.h>

void saxpy(int size, float alpha, float const x[size], float y[size]) {
  for (int i = 0; i < size; i++) {
    y[i] += alpha * x[i];
  }
}

int main(int argc, char* argv[argc + 1]) {
  int size    = 100;
  float alpha = 2.0f;
  float *x, *y;

  y = malloc(size * sizeof(float));
  for (int i = 0; i < size; ++i) {
    x    = malloc(size * sizeof(float));
    x[i] = 50 + i;
    y[i] = i;
  }

  saxpy(size, alpha, x, y);
  for (int i = 0; i < 100; ++i) {
    printf("y[%d] = %f; ", i, y[i]);
    if (0 == (i + 1) % 10) {
      printf("\n");
    }
  }

  return 1;
}
