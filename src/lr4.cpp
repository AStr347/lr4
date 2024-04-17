/**
 * Замечательный ряд
 * Написать программу, которая приближенно вычисляет значение ряда
 * 
 * 1 - (1/(2^4)) + (1/(3^4)) + (1/(4^4)) + L = p^4/720 = 0.94703
 */
#include <mpi.h>
#include <iostream>
#include "arch.h"
#include <cmath>
#include <ctime>

/**
 * calculate 1 value of Wonderful series
 * and send it throw MPI
*/
static
void any_thread(const int rank){
    const int value = rank + 1;
    const int sign = (rank & 1)? -1 : 1;
    const f32 powered = pow((f32)value, 4);
    const f32 result = sign * (1 / powered);
    MPI_Send(&result, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);

    // debug info
    // const char sign_char = (value & 1)? '-' : ' ';
    // std::cout << "calculate:" << sign_char << "1/(" << value << "^4) by tag: " << rank << std::endl;
}

/**
 * collect all values of Wonderful series
 * by MPI
 * and calculate result
*/
static
void zero_thread(const int size){
    const std::clock_t c_start = std::clock();
    f32 result = 1;
    for(int i = 1; i < size; i++){
        f32 value = 0;
        MPI_Status status;
        MPI_Recv(&value, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        const int tag = status.MPI_TAG;
        std::cout << "get value: " << value <<
                     " by tag: " << tag << std::endl;
        
        result += value;
    }
    
    const std::clock_t c_end = std::clock();

    std::cout << "result of Wonderful series: " << result << std::endl;
    std::cout << "mpi_time = " << (1000.0 * (c_end - c_start) / CLOCKS_PER_SEC) << " ms" << std::endl;
}

int main(void) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    int world_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Get the rank of the process
    int world_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(0 != world_rank){
        any_thread(world_rank);
    } else {
        zero_thread(world_size);
    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
