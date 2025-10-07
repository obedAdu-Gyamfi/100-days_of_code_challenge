#include "main.h"




int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    MPI_Status status;
    int rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


    int sendbuf = 20 , recvbuff;
    int dest = 1;

    if (rank == 0){
        printf("Rank %d sends integer value %d\n", rank, sendbuf);
        MPI_Send(&sendbuf, 1 , MPI_INT, 1, 0, MPI_COMM_WORLD);

    }
    else{
        MPI_Recv(&recvbuff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Rank %d received integer %d\n", rank, recvbuff);
    }
    MPI_Finalize();
    return (0);
}