#include "main.h"

/**
 * main - Entry point
 * Description: Uses MPI_Allreduce for global averaging.
 * @argc: Number of command line arguments
 * @argv: A pointer to the command line arguments (array)
 * Return: Always 0 on success
 */

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, nprocs;
    double local_temp;
    double global_temp;
    double temp_avg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    MPI_Barrier(MPI_COMM_WORLD);
    local_temp = 27 + rank;
    MPI_Allreduce(&local_temp, &global_temp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    temp_avg = global_temp / nprocs;
    printf("I am rank %d \t average temperature %lf \n", rank, temp_avg);
    MPI_Finalize();
    return (0);
}