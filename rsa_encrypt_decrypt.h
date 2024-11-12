#pragma once
#define MAX_MESSAGE_LENGTH 2048
typedef struct {
    long long p;
    long long q;
    long long n;
    long long fi;
    long long d;
    long long c;
} user;
long long extended_gcd(long long a, long long b, long long *x, long long *y);

long long mod_inverse(long long d, long long fi);

long long gcd(long long a, long long b);

long long find_coprime(long long n);

long long mod_pow(long long base, long long exp, long long mod);

void init_user_keys(user *u, long long p, long long q);

void encrypt_message(char *message, long long *encrypted, long long d, long long n);


void decrypt_message(long long *encrypted, char *decrypted, int length, long long c, long long n);