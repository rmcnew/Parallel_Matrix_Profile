#include <mpi.h>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>

#include "command_line_args.h"
#include "log.h"
#include "read_time_series_csv.h"
#include "timing.h"
#include "types.h"
#include "write_matrix_profile_csv.h"

#define FALSE 0
#define TRUE 1
#define ONE_MESSAGE 1


int rank;
int process_count;    

CommandLineArgs command_line_args;

DoubleArray time_series;

MatrixProfile matrix_profile;

DoubleArray distance_profile;


// ***** Initializations *****
void initialize_MPI(int argc, char* argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and process count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);  


}

void merge_matrix_profiles(MatrixProfile& matrix_profile, const MatrixProfile& received) {
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        if (received.data[i] < matrix_profile.data[i]) {
            matrix_profile.data[i] = received.data[i];
            matrix_profile.index[i] = received.index[i];
        }
    }
}


int main(int argc, char** argv) {
    // put command line args in string vector
    std::vector<std::string> args(argv + 1, argv + argc);

    initialize_MPI(argc, argv);

    if (rank == LEADER) {
        command_line_args = parse_command_line_args(args);
        validate_command_line_args(command_line_args);
    } 

    start_timer();
    //start_logging();

    if (rank == LEADER) {
        time_series = read_time_series_csv_file(command_line_args.input_file, command_line_args.input_column);
    } 

    // MPI_Bcast time_series to non-Leader processes
    MPI_Bcast(&(time_series.length), ONE_MESSAGE, MPI_UNSIGNED_LONG, LEADER, MPI_COMM_WORLD);
    if (rank != LEADER) {
        time_series.data = (double *) calloc(time_series.length, sizeof(double));
    }
    MPI_Bcast(time_series.data, (int)time_series.length, MPI_DOUBLE, LEADER, MPI_COMM_WORLD);

    // MPI_Bcast window_size to non-Leader processes
    MPI_Bcast(&(command_line_args.window_size), ONE_MESSAGE, MPI_INT, LEADER, MPI_COMM_WORLD);

    // Each process calculates distance profiles for its portion of the time_series indices 
    // and updates its own local matrix_profile using element-wise minimum (STAMP)
    unsigned long exclusion_radius = (unsigned long) command_line_args.window_size / 4;
    matrix_profile = stamp(time_series, command_line_args.window_size, exclusion_radius);

    // Each non-Leader process MPI_Send's local matrix_profile to Leader
    // Leader MPI_Recv's matrix_profiles from non-Leader processes and updates
    // the global matrix_profile using merge_matrix_profiles
    if (rank == LEADER) {
        MatrixProfile received;
        received.length = matrix_profile.length;
        received.data = (long double*) calloc(received.length, sizeof(long double));
        received.index = (unsigned long*) calloc(received.length, sizeof(unsigned long));
        for (int i = 1; i < process_count; i++) {
            MPI_Recv(received.data, (int)matrix_profile.length, MPI_LONG_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD); 
            MPI_Recv(received.index, (int)matrix_profile.length, MPI_UNSIGNED_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD); 
            merge_matrix_profiles(matrix_profile, received);
        }
    } else {
        MPI_Send(matrix_profile.data, (int)matrix_profile.length, MPI_LONG_DOUBLE, LEADER, ONE_MESSAGE, MPI_COMM_WORLD);
        MPI_Send(matrix_profile.index, (int)matrix_profile.length, MPI_UNSIGNED_LONG, LEADER, ONE_MESSAGE, MPI_COMM_WORLD);
    }

    // Leader process writes out global matrix_profile to output_file
    if (rank == LEADER) {
        write_matrix_profile_csv(command_line_args.output_file, matrix_profile);
    }

    stop_timer();
    //stop_logging();

    // Shutdown MPI
    MPI_Finalize();
    if (rank == LEADER) {
        printf("Run completed.  Total elapsed time: %6.2f seconds.  See log files\n", get_overall_elapsed_time());
    }

	return 0;
} 
