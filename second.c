#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    if (N <= 0) {
        printf("Please provide a positive integer for N.\n");
        return 1;
    }
    double sum = 0.0;
    omp_set_num_threads(4); 
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += 1.0 / i;
    }
    printf("Master thread (thread 0) finished computing the sum: %f\n", sum);

    return 0;
}


