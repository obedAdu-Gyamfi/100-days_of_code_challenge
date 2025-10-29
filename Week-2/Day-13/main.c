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

    int dims[2] = {3, 2}; /* an array containing the structure of our 2-D grid, thus creating a 3 processes along  the first dimension (x) row
                            and 2 processes along the sencond dimension (y) columnd */

    int periods[2] = {1, 1}; /* a period of {1, 1} indicates a wrap around on  both axis, thus process loop around the edges to the neighbouring
                             processes*/

    int reorder = true;

    MPI_Dims_create(nprocs, 2, dims);
    MPI_Comm new_communicator;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &new_communicator);

    int my_coords[2];

    MPI_Cart_coords(new_communicator, rank, 2, my_coords);
    int up, down;

    MPI_Cart_shift(new_communicator, 0, 1, &up, &down);

    int left, right;
    MPI_Cart_shift(new_communicator, 1, 1, &left, &right);

    printf("[MPI Process %d] I am located at (%d, %d).\n", rank, my_coords[0], my_coords[1]);
    printf("[MPI Process %d] Up and down neighbours are (%d, %d) and lefft and right neigbours are (%d, %d)\n", rank, up, down, left, right);
    MPI_Finalize();
    return (0);
}