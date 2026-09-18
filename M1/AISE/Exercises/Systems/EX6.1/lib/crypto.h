#ifndef CRYPTO_H
#define CRYPTO_H

int crypto_encrypt(int n1, char *input, int *n2, char **output, int k);
int crypto_decrypt(int n1, char *input, int *n2, char **output, int k);

#endif
