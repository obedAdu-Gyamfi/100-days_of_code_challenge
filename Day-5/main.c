#include "main.h"


int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    double *array = NULL;
    double *local_a = NULL;
    double local_sum;
    double global_sum;
    int start, end, chunk;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int n = atoi(argv[1]);
    start = (rank * n) / nprocs;
    end = ((rank + 1) * n) / nprocs;
    chunk = end - start;

    array = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++){
        array[i] = i * i;
    }
    local_a = (double *)malloc(sizeof(double) * chunk);
    int k = 0;
    for (int j = start; j < end; j++){
        local_a[k] = array[j];
        k += 1;
    }
    for (int i = 0; i < chunk; i++){
        local_sum += local_a[i];
    }
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("I am rank %d \t Local_sum = %lf\n", rank, local_sum);

    /*
    putchar('\n');
    for (int j = 0; j < chunk; j++){
        printf("Rank %d \t local_a[%d] = %lf\n", rank, j, local_a[j]);
    }
    */

    if (rank == 0){
        printf("\n Global Sum = %lf\n", global_sum);
    }
    free(array);
    free(local_a);

    MPI_Finalize();
    return (0);
}