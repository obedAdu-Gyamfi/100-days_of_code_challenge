#include "main.h"

/**
 * main - Entery point
 *
 * Description: Creates a 3-D grid communicator
 * @argc: Number of command line arguments
 * @argv: An array of the command line arguments.
 * Return:
 */

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int dims[2] = {3, 2};
    int periods[2] = {1, 1};
    int reorder = false;

    MPI_Dims_create(nprocs, 2, dims);
    MPI_Comm new_communicator;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &new_communicator);

    int my_coords[2];

    MPI_Cart_coords(new_communicator, rank, 2, my_coords);

    printf("[MPI Process %d] I am located at (%d, %d).\n", rank, my_coords[0], my_coords[1]);
    MPI_Finalize();
    return (0);
}