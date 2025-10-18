#include "main.h"

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank, nprocs;
	

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	printf("Hello wold from process %d of %d cores\n", rank, nprocs);
	MPI_Finalize();
	return (0);

}
