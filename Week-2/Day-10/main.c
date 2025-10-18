#include "main.h"

/**
 * main - Entry point
 * Description: Computes average temperature using MPI_Reduce
 *
 * Return: Always 0 on success
 *
 */

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    double local_temp;
    double global_temp;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    MPI_Barrier(MPI_COMM_WORLD);
    local_temp = 27.0 + rank;

    MPI_Reduce(&local_temp, &global_temp, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Average temperature: %lf \n", (global_temp / nprocs));
    }
    MPI_Finalize();
    return (0);
}