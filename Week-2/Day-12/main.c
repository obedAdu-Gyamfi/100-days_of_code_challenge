#include "main.h"

/**
 * main - Entry point
 * Description: This is an MPI program that implements
 * a parallel prefix sum using MPI_Scan
 *
 * @argc: Number of command line arguments
 * @argv: An array of the command line arguments
 *
 * Return: Always 0 on success
 */

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    int sendbuff, recvbuff;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    sendbuff = rank;

    /*Each  rank sends its rank as a senbuf to the next rank.
    Each rank from n = 1 to n-1 receives the buffer from the previous rank and adds it to its rank and also
    send it to the next rank after it.

    */
    MPI_Scan(&sendbuff, &recvbuff, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("I am rank %d with recvbuff %d\n", rank, recvbuff);

    MPI_Finalize();
    return (0);
}