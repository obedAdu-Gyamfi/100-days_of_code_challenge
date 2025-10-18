#include "main.h"


int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    int start, end, chunk;
    int r_start, r_end, r_chunk;
    double *array = NULL;
    double *local_a = NULL;
    double local_sum = 0;
    double global_sum = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int n =  atoi(argv[1]);
    start = (rank * n) / nprocs;
    end = ((rank + 1) * n) / nprocs;
    chunk = end - start;

    int *sendcount = (int *)malloc(sizeof(int) * nprocs);
    int *displ = (int *)malloc(sizeof(int) * nprocs);
    if (rank == 0){
        array = (double *)malloc(sizeof(double) * n);
        for (int i = 0; i < n; i++){
            array[i] = i * i;
        }
        for (int j = 0; j < nprocs; j++){
            r_start = (j * n) / nprocs;
            r_end = ((j + 1) * n) / nprocs;
            r_chunk = r_end - r_start;
            sendcount[j] = r_chunk;
            displ[j] = r_start;
            
        }
    }
    local_a = (double *)malloc(sizeof(double) * chunk);
    MPI_Scatterv(array, sendcount, displ, MPI_DOUBLE, local_a, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    double s_time, e_time, p_time;
    s_time = MPI_Wtime();
    for (int j = 0; j < chunk; j++){
        local_sum += local_a[j];
    }
    e_time = MPI_Wtime();
    p_time = (double)(e_time - s_time);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0){
        printf("Global Sum = %lf\nOperation completed in %lf secs\n", global_sum, p_time);
        free(array);
    }
    free(sendcount);
    free(displ);
    free(local_a);

    MPI_Finalize();
    return (0);
}