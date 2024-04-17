#include <mpi.h>
#include <iostream>

int main(void) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len = 0;
    MPI_Get_processor_name(processor_name, &name_len);

    // Finalize the MPI environment.
    MPI_Finalize();

    // Print off a hello world message
    std::cout << "Hello world from processor: " << processor_name << " rank: " << world_rank << " out of " << world_size << " processors" << std::endl;
}
