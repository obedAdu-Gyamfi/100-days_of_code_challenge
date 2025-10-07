#include "main.h"

int main(int argc, char **argv){

    MPI_Init(&argc, &argv);
    int rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    char hostname[MPI_MAX_PROCESSOR_NAME];
    int namelen = 0;
    
    if (rank == 0){
        MPI_Get_processor_name(hostname, &namelen);

    }
    MPI_Bcast(&namelen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(hostname, namelen + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("Rank %d received the broadcast meassage  %s from rank 0\n", rank, hostname);
    

    MPI_Finalize();
    return (0);
}