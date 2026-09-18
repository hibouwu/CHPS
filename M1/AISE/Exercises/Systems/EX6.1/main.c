#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int main(){
    int n_int;
    char *out;
    int n = 6;
    char * clear = malloc(n*sizeof(char));
    strcpy(clear, "Hello");
    int k = 3;
    printf("Texte clair : %s\n", clear);
    crypto_encrypt(n, clear, &n_int, &out, k);
    printf("Texte chiffré : ");
    for(int i = 0; i < n_int; i++){
        printf("%c", out[i]);
    }
    printf("\n");
    crypto_decrypt(n_int, out, &n, &clear, k);
    printf("Texte déchiffré : %s\n", clear);
    free(clear);
    free(out);
    return 0;

    
}