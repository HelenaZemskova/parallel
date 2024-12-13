#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv) {
    omp_set_num_threads((int)atoi(argv[1]));
    double **a = (double **)malloc(ISIZE * sizeof(double *));
    for (int i = 0; i < ISIZE; i++) 
    {
        a[i] = (double *)malloc(JSIZE * sizeof(double));
    }
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ISIZE; i++) 
    {
        for (int j = 0; j < JSIZE; j++) 
        {
            a[i][j] = 10 * i + j;
        }
    }
    double start_time = omp_get_wtime();
    for (int i = 0; i < ISIZE - 1; i++) 
    {
        #pragma omp parallel for
        for (int j = 6; j < JSIZE; j++) 
        {
            a[i][j] = sin(0.2 * a[i + 1][j - 6]);
        }
    }
    double end_time = omp_get_wtime();
    FILE *ff = fopen("1dpar.txt", "w");
    for (int i = 0; i < ISIZE; i++) 
    {
        for (int j = 0; j < JSIZE; j++) 
        {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
    fclose(ff);
    printf("Time taken: %f seconds\n", end_time - start_time);
    for (int i = 0; i < ISIZE; i++) 
    {
        free(a[i]);
    }
    free(a);

    return 0;
}
