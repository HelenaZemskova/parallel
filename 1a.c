#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv)
{
    double **a = (double **)malloc(ISIZE * sizeof(double *)); 
    if (a == NULL) {
        printf("Memory allocation failed for rows!\n");
        return 1;
    }
    for (int i = 0; i < ISIZE; i++) {
        a[i] = (double *)malloc(JSIZE * sizeof(double)); 
        if (a[i] == NULL) {
            printf("Memory allocation failed for columns at row %d!\n", i);
            return 1;
        }
    }

    int i, j;
    FILE *ff;
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    clock_t start = clock();
    for (i = 1; i < ISIZE; i++) {
        for (j = 0; j < JSIZE - 1; j++) {
            a[i][j] = sin(2 * a[i - 1][j + 1]);
        }
    }
    clock_t end = clock();
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    ff = fopen("1a.txt", "w");
    if (ff == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
    fclose(ff);

    for (i = 0; i < ISIZE; i++) {
        free(a[i]); 
    }
    free(a); 

    return 0;
}



