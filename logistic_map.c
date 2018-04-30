#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define LOOP 10
#define P 6700417
#define MU 22
#define NUM_VALUES 0x2000000

static int logisticsmap_calc(int x, int p, int mu) {
    return mu * x * (x + 1) % p;
}

static int logisticsmap_loopCalc(int num, int x, int p, int mu) {
    for(int i = 0; i < num; i++) {
        x = logisticsmap_calc(x, p, mu);
    }
    return x;
}

void benchmark() {
	const int mu = MU;
	const int p = P;
	int *x;
	x = (int *)malloc(sizeof(int) * NUM_VALUES);

	for(int i = 1; i < NUM_VALUES; i++) {
		x[i] = i;
	}
	for(int i = 1; i < NUM_VALUES; i++) {
		x[i] = logisticsmap_loopCalc(LOOP, x[i], p, mu);
	}
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
