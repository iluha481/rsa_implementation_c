#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 10000
#define MAX 99999


long long get_rand(long long min, long long max){
    return min + rand() % (max - min + 1); 
}


long long modular_pow(long long base, long long exp, long long mod){
    long long result = 1;
    base %= mod;
    while (exp > 0){
        if (exp % 2 == 1 ) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /=2;
    }
    return result;
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
        long long x = modular_pow(a, d, n);
        if( x == 1 || x == n-1) continue;
        
        int composite = 1;
        for (int r = 0; r < s - 1; r++) {
            x = modular_pow(x, 2, n);
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


int main() {
    srand(time(NULL));
    printf("%lld", get_rand_prime(MIN, MAX));
    

    return 0;
}