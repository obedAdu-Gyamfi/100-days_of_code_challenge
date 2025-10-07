#include "main.h"


int main(int argc, char **argv){

	MPI_Init(&argc, &argv);
	int start, end, chunk;
	int rank, nprocs;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	int n = atoi(argv[1]);
	start = (rank * n) / nprocs;
	end = ((rank + 1) * n )/ nprocs;
	chunk = end - start;


	double myarr[n];
	for (int i = 0; i < n; i++){
		myarr[i] = i * i;
    }
	double local_arr[chunk];
	int k = 0;
	for (int j = start; j < end ; j++){
		local_arr[k] = myarr[j];
		k += 1;
    }
	MPI_Barrier(MPI_COMM_WORLD);

	for (int j = 0; j < chunk; j++){
		printf("Rank %d \t local_arr[%d] \t %lf\n", rank,  j, local_arr[j]);
    }
	MPI_Finalize();
	return (0);
}