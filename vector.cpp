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
	if (world_size < 2)
	{
		fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	int vector_size = 15;
	int vector[vector_size];
	int num_positions = vector_size / (world_size - 1);

	if (world_rank == 0)
	{

		for (int i = 0; i < vector_size; i++)
		{
			vector[i] = i;
		}

		int last_pos = 0;
		for (int i = 0; i < (world_size - 1); i++)
		{
			int arr_to_send[num_positions];
			for (int j = 0; j < num_positions; j++)
			{
				arr_to_send[j] = vector[last_pos];
				last_pos++;
			}
			// data, count, datatype, source, tag, communicator
			MPI_Send(&arr_to_send, num_positions, MPI_INT, (i + 1), 0, MPI_COMM_WORLD);
		}

		int vector_value = 0;
		for (int i = 0; i < (world_size - 1); i++)
		{
			int value = 0;
			MPI_Recv(&value, 1, MPI_INT, (i + 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			vector_value += value;
		}

		std::cout << "Sum value: " << vector_value << std::endl;
	}
	else if (world_rank == 1)
	{
		int arr_to_send[num_positions];
		MPI_Recv(&arr_to_send, num_positions, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = arr_to_send[0];
		for (int i = 1; i < num_positions; i++)
		{
			sum += arr_to_send[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 2)
	{
		int arr_to_send[num_positions];
		MPI_Recv(&arr_to_send, num_positions, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = arr_to_send[0];
		for (int i = 1; i < num_positions; i++)
		{
			sum += arr_to_send[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 3)
	{
		int arr_to_send[num_positions];
		MPI_Recv(&arr_to_send, num_positions, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = arr_to_send[0];
		for (int i = 1; i < num_positions; i++)
		{
			sum += arr_to_send[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}