#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv)
{
    int rank, size;
    double end_time, start_time;
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
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = ISIZE / size;
    int start_row = rank * rows_per_process;
    int end_row = (rank == size - 1) ? (ISIZE - 1) : (start_row + rows_per_process);

    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    double tempRow[JSIZE];

    for (i = 1; i < ISIZE; i++) {
        for (j = start_row; j < end_row; j++) {
            a[i][j] = sin(2 * a[i - 1][j + 1]);
        }

        if (rank != 0) {
            MPI_Send(&a[i][start_row], rows_per_process, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            MPI_Recv(&a[i][0], JSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else {
            for (int p = 1; p < size; p++) {
                MPI_Recv(&tempRow[0], rows_per_process, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int p_mul_portion_size = p * rows_per_process;
                for (int k = 0; k < rows_per_process; k++) {
                    a[i][p_mul_portion_size + k] = tempRow[k];
                }
            }
            for (int p = 1; p < size; p++) {
                MPI_Send(&a[i][0], JSIZE, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
            }
        }
    }
    if (rank == 0) {
        end_time = MPI_Wtime();
    }
    if (rank == 0) {
        ff = fopen("1apar.txt", "w");
        for (i = 0; i < ISIZE; i++) {
            for (j = 0; j < JSIZE; j++) {
                fprintf(ff, "%f ", a[i][j]);
            }
            fprintf(ff, "\n");
        }
        fclose(ff);
    }
    if (rank == 0) {
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    for (i = 0; i < ISIZE; i++) {
        free(a[i]);
    }
    free(a);

    MPI_Finalize();
    return 0;
}









