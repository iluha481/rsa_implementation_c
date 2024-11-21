#include "rsa_encrypt_decrypt.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    user u;
    int choice;
    
    do {
        printf("\n=== Menu ===\n");
        printf("1. Init keys\n");
        printf("2. Encrypt message\n");
        printf("3. Decrypt message\n");
        printf("4. Clear console\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                init_user_keys(&u, get_rand_prime(MIN, MAX), get_rand_prime(MIN, MAX));   
                break;
            case 2:
                input_encrypt();
                break;
            case 3:
                input_decrypt();
                break;
            case 4:
                system("cls\n");
                break;
            case 0:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choose\n");
        }
    } while (choice != 0);

    return 0;
}