#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rsa_encrypt_decrypt.h"


// Расширенный алгоритм Евклида
long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

// Функция для нахождения мультипликативного обратного
long long mod_inverse(long long d, long long fi) {
    long long x, y;
    long long gcd = extended_gcd(d, fi, &x, &y);

    if (gcd != 1) {
        printf("Обратного элемента не существует.\n");
        return -1;
    }

    x = (x % fi + fi) % fi;
    return x;
}

// Функция для вычисления НОД двух чисел
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для поиска первого числа, взаимно простого с n
long long find_coprime(long long n) {
    long long candidate = 2;
    while (gcd(n, candidate) != 1) {
        candidate++;
    }
    return candidate;
}

// Функция для возведения в степень по модулю
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Функция инициализации ключей пользователя
void init_user_keys(user *u, long long p, long long q) {
    u->p = p;
    u->q = q;
    u->n = u->p * u->q;
    u->fi = (u->p - 1) * (u->q - 1);
    u->d = find_coprime(u->fi);
    u->c = mod_inverse(u->d, u->fi);

    printf("User keys\np: %lld \nq: %lld \n\npublic key N: %lld  \npublic key d: %lld \nprivate key c: %lld\n\n",
            u->p, u->q, u->n,  u->d, u->c);
    FILE *file = fopen("user_keys.txt", "w");
    if(file != NULL){
        fprintf(file, "%lld\n%lld\n%lld\n",
                u->n, u->d, u->c);
        fclose(file);
    }
}

// Функция шифрования строки
void encrypt_message(char *message, long long *encrypted, long long d, long long n) {
    for (int i = 0; i < strlen(message); i++) {
        encrypted[i] = mod_pow((long long)message[i], d, n);
    }
}

// Функция расшифровки строки
void decrypt_message(long long *encrypted, char *decrypted, int length, long long c, long long n) {
    for (int i = 0; i < length; i++) {
        decrypted[i] = (char)mod_pow(encrypted[i], c, n);
    }
    decrypted[length] = '\0';
}
    



long long get_rand(long long min, long long max){
    return min + rand() % (max - min + 1); 
}


int is_prime(long long n, int k){
    if (n < 2) return 0;
    if (n != 2 && n % 2 == 0) return 0;
    
    long long d = n - 1;
    int s = 0;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }
    
    for (int i = 0; i < k; i ++){
        long long a = 2 + rand() % (n - 3);
        long long x = mod_pow(a, d, n);
        if( x == 1 || x == n-1) continue;
        
        int composite = 1;
        for (int r = 0; r < s - 1; r++) {
            x = mod_pow(x, 2, n);
            if (x == n - 1) {
                composite = 0;
                break;
            }
        }
        if (composite) return 0; 
    }
    return 1; 
}


long long get_rand_prime(long long min, long long max){
    long long prime_num;
    do{
        prime_num = get_rand(min,max);
    }while(!is_prime(prime_num, 40));
    
    return prime_num;
    
}



void input_decrypt(){
    long long c, n;
    int length;


    printf("Enter your private key c and public key n: ");
    scanf("%lld %lld", &c, &n);
    printf("\n");

    printf("Enter message length: ");
    scanf("%d", &length);

    long long encrypted_message[length + 1];
    printf("Enter encrypted message: ");
    for(int i = 0; i < length; i++){
        scanf("%lld", &encrypted_message[i]);
    }

    char decrypted_message[length + 1];

    decrypt_message(encrypted_message, decrypted_message, length, c, n);
    printf("Decrypted message:\n %s\n", decrypted_message);
}


void input_encrypt(){
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
}

void input_user_keys(user *u, const char *filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open keys file");
        return;
    }

    long long n, d, c;

    if (fscanf(file, "%lld %lld %lld", &n, &d, &c)!= 3) {
        printf("Error reading keys from file.\n");
        fclose(file);
        return;
    }
    fclose(file);

    u->n = n;
    u->d = d; 
    u->c = c;
    printf("User keys loaded from file:\n");
    printf("n: %lld \nd: %lld \nc: %lld", u->n, u->d, u->c);
}

void file_input_decrypt(user *u,const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("Failed to open input file");
        return;
    }

    int length;
    if (fscanf(input_file, "%d", &length) != 1) {
        printf("Error reading message length from input file.\n");
        fclose(input_file);
        return;
    }

    long long encrypted_message[length];
    for (int i = 0; i < length; i++) {
        if (fscanf(input_file, "%lld", &encrypted_message[i]) != 1) {
            printf("Error reading encrypted message from input file.\n");
            fclose(input_file);
            return;
        }
    }
    fclose(input_file);

    char decrypted_message[length + 1];
    decrypt_message(encrypted_message, decrypted_message, length, u->c, u->n);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        return;
    }

    fprintf(output_file, "Decrypted message:\n%s\n", decrypted_message);
    fclose(output_file);
}

void file_input_encrypt(user *u, const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("Failed to open input file");
        return;
    }

    char message[MAX_MESSAGE_LENGTH];
    if (!fgets(message, MAX_MESSAGE_LENGTH, input_file)) {
        printf("Error reading message from input file.\n");
        fclose(input_file);
        return;
    }
    fclose(input_file);

    int length = strlen(message);
    if (message[length - 1] == '\n') {
        message[length - 1] = '\0'; // Убираем символ новой строки
        length--;
    }

    long long encrypted[length];
    encrypt_message(message, encrypted, u->d, u->n);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        return;
    }

    fprintf(output_file, "%d\n", length);
    for (int i = 0; i < length; i++) {
        fprintf(output_file, "%lld ", encrypted[i]);
    }
    fprintf(output_file, "\n");
    fclose(output_file);
}
