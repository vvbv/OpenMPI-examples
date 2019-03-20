#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{

	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	// Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// We are assuming at least 2 processes for this task
	if (world_size < 2){
		fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	int vector_size = 20;
	int number[ vector_size ];

	if (world_rank == 0){
		int segments = vector_size / world_size;
		for (int i = 0; i < vector_size; i++){
			number[i] = i;
		}
		// data, count, datatype, source, tag, communicator
		MPI_Send( &number, vector_size, MPI_INT,1,0,MPI_COMM_WORLD);
	}else if (world_rank == 1){
		MPI_Recv(&number, vector_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	MPI_Finalize();
}