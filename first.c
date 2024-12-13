#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please provide a positive integer for the number of threads.\n");
        return 1;
    }
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        /* #pragma omp for ordered
        for (int i = 0; i < n; i++) {
            #pragma omp ordered
            {
                printf("Hello World from thread %d\n", i);
            } 
            
        } */
        int id = omp_get_thread_num();
            printf("Hello World from thread %d\n", id);
    }

    return 0;
}

