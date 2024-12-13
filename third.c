#include <omp.h>
#include <stdio.h>

int main() {
    int shared_var = 0;
    int num_threads = 4;
    omp_set_num_threads(num_threads);
    #pragma omp parallel for ordered
    for (int i = 0; i < num_threads; i++) {
        #pragma omp ordered
        {
            shared_var++;
            int thread_id = omp_get_thread_num();
            printf("Thread %d accessed the shared variable. Current value: %d\n", thread_id, shared_var);
        }
    }

    return 0;
}


