#include "rsa_encrypt_decrypt.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main(){
    long long c, n;
    int length;


    printf("Enter your private key c and public key n: ");
    scanf("%lld %lld", &c, &n);
    printf("\n");

    printf("Enter message length: ");
    scanf("%d", &length);

    long long encrypted_message[length + 1];
    for(int i = 0; i < length; i++){
        scanf("%lld", &encrypted_message[i]);
    }

    char decrypted_message[length + 1];

    decrypt_message(encrypted_message, decrypted_message, length, c, n);
    printf("Decrypted message:\n %s\n", decrypted_message);
    system ("pause");
    return 0;
}