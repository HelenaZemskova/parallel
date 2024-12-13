#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define ISIZE 5000
#define JSIZE 5000

int main(int argc, char **argv)
{   
    int i, j;
    FILE *ff;
    double end_time, start_time;
    double **a = (double **)malloc(ISIZE * sizeof(double *));
    if (a == NULL) {
        printf("Memory allocation failed for rows!\n");
        return 1;
    }
    for (i = 0; i < ISIZE; i++) {
        a[i] = (double *)malloc(JSIZE * sizeof(double));
        if (a[i] == NULL) {
            printf("Memory allocation failed for columns at row %d!\n", i);
            return 1;
        }
    }

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }

    int rows_per_process = ISIZE / size;
    int start_row = rank * rows_per_process;
    int end_row = (rank == size - 1) ? ISIZE : (start_row + rows_per_process);

    if (rank == 0) {
        start_time = MPI_Wtime();
    }
    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = sin(2 * a[i][j]);
        }
    }
    if (rank == 0) {
        for (i = 1; i < size; i++) {
            int rows = (i == size - 1) ? (ISIZE - rows_per_process * i) : rows_per_process;
            for (int r = rows_per_process * i; r < rows_per_process * i + rows; r++) {
                MPI_Recv(a[r], JSIZE, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    } else {
        for (i = start_row; i < end_row; i++) {
            MPI_Send(a[i], JSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    if (rank == 0) {
        ff = fopen("mainpar_mpi.txt", "w");
        if (ff == NULL) {
            printf("Error opening file for writing\n");
            MPI_Finalize();
            return 1;
        }
        for (i = 0; i < ISIZE; i++) {
            for (j = 0; j < JSIZE; j++) {
                fprintf(ff, "%f ", a[i][j]);
            }
            fprintf(ff, "\n");
        }
        fclose(ff);
    }
    for (i = 0; i < ISIZE; i++) {
        free(a[i]);
    }
    free(a);

    MPI_Finalize();
    return 0;
}









