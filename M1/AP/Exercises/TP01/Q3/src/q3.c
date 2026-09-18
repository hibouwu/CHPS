#include <stdio.h>
#include <stdint.h>


int64_t arraymin(size_t n, int64_t array[n]) {
  if(n == 0)
    return 0;
  if(n == 1)
    return array[0];

  int64_t min = array[0];
  for(size_t i=1; i<n; ++i) {
    if(array[i] < min)
      min = array[i];
  }

  return min;
}


int64_t arraymin_asm(size_t n, int64_t array[n]) {
  int64_t min = 0;
  asm(
    "cmp %1, 0;"
    "je end;"

    "mov %0, [%2];" // Initial min element is the 1st one...
    "cmp %1, 1;"
    "je end;"

    "mov rax, 1;" // Thus, start iterating from index 1
    "start:"
    
    "mov r8, [%2+rax*8];"
    "cmp r8, %0;"
    "jge inc;"
    "mov %0, r8;" // Save the current element (r8) in the min element (%0)
    "inc:"
    "inc rax;"
    "cmp rax, %1;"
    "jl start;"
    
    "end:"
    : "+r" (min)
    : "r" (n), "r" (array)
    : "rax", "r8"
  );

  return min;
}

int main(void) {
  int64_t array[5] = {-1, 5, 2, -5, 4};

  int64_t min = arraymin(5, array);
  printf("min=%d\n", min);

  min = arraymin_asm(5, array);
  printf("asm min=%d\n", min);

  return 0;
}