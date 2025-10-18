#include "main.h"


int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    MPI_Status status;
    

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


    int sendbuf = rank + 2;
    int dest = (rank  + 1) % nprocs;
    int source = rank == 0 ? nprocs - 1 : rank - 1 ;
    int recvbuf;

    if (rank % 2 == 0){
        MPI_Send(&sendbuf, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        MPI_Recv(&recvbuf, 1 , MPI_INT, source, 0, MPI_COMM_WORLD, &status);
    }
    else{
        MPI_Recv(&recvbuf, 1 , MPI_INT, source, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&sendbuf, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    printf("I am rank %d \t Received %d from %d \t sent %d to %d\n", rank, recvbuf, source, sendbuf, dest);

    MPI_Finalize();
    return (0);
}