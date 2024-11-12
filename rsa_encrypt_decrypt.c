#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

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
    
