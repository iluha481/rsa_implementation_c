#include "rsa_encrypt_decrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    user u;
    int choice;
    
    do {
        printf("\n=== Menu ===\n");
        printf("1. Init keys\n");
        printf("2. Input keys from user_keys.txt\n");
        printf("3. Encrypt message\n");
        printf("4. Decrypt message\n");
        printf("5. Encrypt message from encrypt_input.txt to encrypt_output.txt\n");
        printf("6. Decrypt message from decrypt_input.txt to decrypt_output.txt\n");
        printf("7. Clear console\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                init_user_keys(&u, get_rand_prime(MIN, MAX), get_rand_prime(MIN, MAX));   
                break;
            case 2:
                input_user_keys(&u,"user_keys.txt");
                break;
            case 3:
                input_encrypt();
                break;
            case 4:
                input_decrypt();
                break;
            
            case 5:
                file_input_encrypt(&u, "encrypt_input.txt", "encrypt_output.txt");
                break;
            case 6:
                file_input_decrypt(&u, "decrypt_input.txt", "decrypt_output.txt");
                break;
            case 7:
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