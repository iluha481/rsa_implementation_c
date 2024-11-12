#include "rsa_encrypt_decrypt.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main(){
    long long public_key_d;
    long long public_key_n;
    char message[MAX_MESSAGE_LENGTH];
    printf("Enter public keys N and d: ");
    scanf("%lld %lld", &public_key_n, &public_key_d);
    getchar();  // Очищаем буфер ввода, чтобы fgets работал корректно

    printf("Enter message to encrypt: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    
    int length = strlen(message);
    if (message[length - 1] == '\n') {
        message[length - 1] = '\0';  // Убираем символ новой строки в конце строки
        length--;  // Уменьшаем длину на 1, если убрали символ новой строки
    }

    long long encrypted[length];
    encrypt_message(message, encrypted, public_key_d, public_key_n);
    printf("Message length: %d\n", length);

    printf("Encrypted message: \n");
    for (int i = 0; i < length; i++) {
        printf("%lld ", encrypted[i]);
    }
    printf("\n");
    system ("pause");
    return 0;
}
