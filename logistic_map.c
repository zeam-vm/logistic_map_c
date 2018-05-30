#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#define LOOP 10
#define P 6700417
#define MU 22
#define NUM_VALUES 0x2000000

static int64_t logisticsmap_calc(int64_t x, int64_t p, int64_t mu) {
    return mu * x * (x + 1) % p;
}

static int64_t logisticsmap_loopCalc(int64_t num, int64_t x, int64_t p, int64_t mu) {
    for(int64_t i = 0; i < num; i++) {
        x = logisticsmap_calc(x, p, mu);
    }
    return x;
}

void benchmark() {
    const int64_t mu = MU;
    const int64_t p = P;
    int64_t *x;

    x = (int64_t *)malloc(sizeof(int64_t) * NUM_VALUES);

    for(int i = 1; i < NUM_VALUES; i++) {
        x[i] = i;
    }
    for(int i = 1; i < NUM_VALUES; i++) {
        x[i] = logisticsmap_loopCalc(LOOP, x[i], p, mu);
    }

    printf("1: %lld, 10000: %lld\n", x[1], x[10000]);

    free(x);
}

int main() {
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    benchmark();
    
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    time_t diffsec = difftime(end_time.tv_sec, start_time.tv_sec);
    suseconds_t diffsub = end_time.tv_usec - start_time.tv_usec;
    double realsec = diffsec + diffsub * 1e-6;
    printf("%f sec\n", realsec);

	return EXIT_SUCCESS;	
}
