#include "main.h"


int main(int argc, char **argv){
	int rank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	char hostname[MPI_MAX_PROCESSOR_NAME];
	int namelen;

	MPI_Get_processor_name(hostname, &namelen);
	printf("I am process %d of %d processes on %s\n", rank, nprocs, hostname);
	MPI_Finalize();
	return (0);
}