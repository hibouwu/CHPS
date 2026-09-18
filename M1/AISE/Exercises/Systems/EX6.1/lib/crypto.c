#include <stdlib.h>
#include "crypto.h"

int crypto_encrypt(int n1, char *input, int *n2, char **output, int k){
    *n2 = n1;
    *output = malloc((*n2) * sizeof(char));
    if (!(*output)) return 1;
    for(int i = 0; i < n1; i++){
        (*output)[i] = input[i] + k;
    }
    return 0;
}

int crypto_decrypt(int n1, char *input, int *n2, char **output, int k){
    *n2 = n1;
    *output = malloc((*n2) * sizeof(char));
    if (!(*output)) return 1;
    for(int i = 0; i < n1; i++){
        (*output)[i] = input[i] - k;
    }
    return 0;
}
