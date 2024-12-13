#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ISIZE 5000
#define JSIZE 5000
int main(int argc, char **argv)
{
    time_t start, end;
    double * * a = (double**) malloc(ISIZE * sizeof(double*));
    for (int i = 0; i < ISIZE; i++) {
        a[i] = (double*)malloc(JSIZE * sizeof(double));
    }
    int i, j;
    FILE *ff;
    for (i=0; i<ISIZE; i++){
    for (j=0; j<JSIZE; j++){
    a[i][j] = 10*i +j;
    }
    }
    start = time(NULL);
    for (i=0; i<ISIZE; i++){
        for (j = 0; j < JSIZE; j++){
            a[i][j] = sin(2*a[i][j]);
        }
    }
    end = time(NULL);
    printf("Time taken: %ld seconds\n", (long)difftime(end, start));
    ff = fopen("main.txt","w");
    for(i=0; i < ISIZE; i++){
        for (j=0; j < JSIZE; j++){
            fprintf(ff,"%f ",a[i][j]);
        }
        fprintf(ff,"\n");
    }
    fclose(ff);
}
