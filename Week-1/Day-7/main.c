#include "main.h"

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, nprocs;


    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    char hostname[MPI_MAX_PROCESSOR_NAME];
    int namelen;


    MPI_Get_processor_name(hostname, &namelen);


    MPI_Barrier(MPI_COMM_WORLD);
    double s_time, e_time, p_time;
    s_time = MPI_Wtime();
    printf("I am rank %d on hostname %s\n", rank , hostname);
    e_time = MPI_Wtime();
    p_time = (double)(e_time - s_time);
    if (rank == 0){
        printf("Operations compeleted in %lf secs\n", p_time);
    }
    MPI_Finalize();
    return (0);
}