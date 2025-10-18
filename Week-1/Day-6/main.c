#include "main.h"


int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    double *array = NULL;
    double *local_a = NULL;
    double *g_array = NULL;
    double local_sum;
    double global_sum;
    int start, end, chunk;
    int r_start, r_end, r_chunk;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int n = atoi(argv[1]);
    start = (rank * n) / nprocs;
    end = ((rank + 1) * n) / nprocs;
    chunk = end - start;
    local_a = (double *)malloc(sizeof(double) * chunk);
    if (rank == 0){
        array = (double *)malloc(sizeof(double) * n);
        for (int i = 0; i < n; i++){
            array[i] = i * i;
        }
        g_array = (double *)malloc(sizeof(double) * nprocs);
    }
    MPI_Scatter(array, chunk, MPI_DOUBLE, local_a, chunk,MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
 
    for (int i = 0; i < chunk; i++){
        local_sum += local_a[i];
    }
    MPI_Gather(&local_sum, 1, MPI_DOUBLE, g_array, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    if (rank == 0){
        for (int i = 0; i < nprocs; i++){
            global_sum += g_array[i];
            printf("Gathered[%d] \t %lf\n", i, g_array[i]);
        }
    }

    if (rank == 0){
        printf("\nGlobal sum = %lf\n", global_sum);
        free(array);
        free(g_array);
    }
    free(local_a);

    MPI_Finalize();
    return (0);
}