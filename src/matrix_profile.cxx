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


int main(int argc, char** argv) {
    // put command line args in string vector
    std::vector<std::string> args(argv + 1, argv + argc);

    initialize_MPI(argc, argv);

    command_line_args = parse_command_line_args(args);
    for (auto arg = args.begin(); arg != args.end(); arg++) {
        if (*arg == "-h" || *arg == "--help") {
            print_usage();
            MPI_Finalize();
            exit(EXIT_SUCCESS);
        }
    bool valid = validate_command_line_args(command_line_args);
        // if invalid, print usage and exit 
    if (!valid) {
        print_usage();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    start_timer();
    //start_logging();

    // MPI_Bcast time_series to non-Leader processes

    // MPI_Bcast window_size to non-Leader processes

    // Each process calculates distance profiles for its portion of the time_series indices 
    // and updates its own local matrix_profile using element-wise minimum (STAMP)

    // Each non-Leader process MPI_Send's local matrix_profile to Leader
    // Leader MPI_Recv's matrix_profiles from non-Leader processes and updates
    // the global matrix_profile using element-wise minimum (see STAMP)

    // Leader process writes out global matrix_profile to output_file

    stop_timer();
    //stop_logging();

    // Shutdown MPI
    MPI_Finalize();
    if (rank == LEADER) {
        printf("Run completed.  Total elapsed time: %'6.2f seconds.  See log files\n", get_overall_elapsed_time());
    }

	return 0;
} 
