#include "rsa_encrypt_decrypt.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main(){
    user u;
    printf("Enter 2 prime numbers p and q: ");
    long long p, q;
    scanf("%lld %lld", &p, &q);
    // Инициализация значений p и qsystem("pause"):
    init_user_keys(&u, p, q);   
    system("pause");
    return 0;
}