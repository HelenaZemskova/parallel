#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <number of threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);
    printf("Number of threads: %d\n", num_threads);
    double **a = (double**) malloc(ISIZE * sizeof(double*));
    if (a == NULL) {
        printf("Memory allocation failed for 'a'\n");
        exit(1);
    }

    for (int i = 0; i < ISIZE; i++) {
        a[i] = (double*)malloc(JSIZE * sizeof(double));
        if (a[i] == NULL) {
            printf("Memory allocation failed for 'a[%d]'\n", i);
            exit(1);
        }
    }

    int i, j;
    FILE *ff;
    printf("Initializing array...\n");
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    double start_time = omp_get_wtime();
    printf("Starting parallel computation...\n");

    #pragma omp parallel for collapse(2)
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = sin(2 * a[i][j]);
        }
    }

    double end_time = omp_get_wtime();
    printf("Writing results to file...\n");
    ff = fopen("mainpar_openmp.txt", "w");
    if (ff == NULL) {
        printf("Failed to open file for writing.\n");
        exit(1);
    }

    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
    fclose(ff);

    printf("Time taken: %f seconds\n", end_time - start_time);

    for (i = 0; i < ISIZE; i++) {
        free(a[i]);
    }
    free(a);

    return 0;
}

