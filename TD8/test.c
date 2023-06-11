//thread
#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#pragma GCC optimize("unroll-loops")
#define N 4000000
#define K 7
uint_fast64_t a[(N + 1) / 64 + !!((N + 1) % 64)];
void *threadBehaviour(void *) {
static uint16_t k = 0;
k = (k + 1) % K;
uint_fast64_t nb_max_i;
for (uint_fast64_t i = 3; i <= sqrt(N); i += 2) {
if (!(a[i / 64] & ((uint_fast64_t)1 << (i % 64))))
continue;
nb_max_i = ((N) - (i * i)) / i;
uint_fast64_t exitCondition = i * i + (nb_max_i * (k + 1) / K) * i;
for (uint_fast64_t j = i * i + (nb_max_i * k / K) * i; j <= exitCondition;
j += i) {
a[j / 64] &= ~(((uint_fast64_t)1) << (j % 64));
}
}
pthread_exit(NULL);
}
int main() {
pthread_t k[K];
for (uint_fast64_t i = 0; i < ((N + 1) / 64 + !!((N + 1) % 64)); i++) {
a[i] = 0xAAAAAAAAAAAAAAAA;
}
for (uint16_t u = 0; u < K; u++) {
pthread_create(&k[u], NULL, &threadBehaviour, NULL);
}
clock_t t;
t = clock();
for (uint16_t j = 0; j < K; j++) {
pthread_join(k[j], NULL);
}
t = clock() - t;
double time_taken = ((double)t) / CLOCKS_PER_SEC;
printf("%f seconds", time_taken);
/*
for(uint_fast64_t i = 2; i < (N+1); i++){
if(a[i/64] & ((uint_fast64_t)1<<i)){
printf("| %lu ", i);
}
}
SR02 Recueil de TDs
*/
printf("\n");
return 0;
}