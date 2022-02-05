#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv) {
    int size, rank;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int hostname_size;

    // initialize MPI environment
    MPI_Init(&argc, &argv);

    // get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get rank of this process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // get hostname of this processor
    MPI_Get_processor_name(hostname, &hostname_size);

    // print hello world message
    printf("Hello from %s, rank %d of %d processors\n", hostname, rank, size);

    // finalize MPI environment
    MPI_Finalize();

	return 0;
} 
