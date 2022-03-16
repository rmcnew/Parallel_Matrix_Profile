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


// Globals for sending and receiving
struct outbound_message {
    int data;
    int destination;
    int tag;
};

int inbound_data;
bool inbound_request_in_progress = false;
MPI_Request inbound_request;

outbound_message outbound_data;
bool outbound_request_in_progress = false;
MPI_Request outbound_request;
std::queue<outbound_message> outbound_queue;





// ***** Message Handling *****
void receive_inbound_messages() {
    int data_ready;
    MPI_Status status;

    do {
        if (!inbound_request_in_progress) {
            MPI_Irecv(&inbound_data, ONE_MESSAGE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &inbound_request);
            inbound_request_in_progress = true;
            data_ready = FALSE;
        }
        if (inbound_request_in_progress) {
            MPI_Test(&inbound_request, &data_ready, &status);
        }
        if (data_ready) {
            inbound_request_in_progress = false;

            // do something with inbound data
        }
    } while (!inbound_request_in_progress);
}

void send_outbound_messages() {
    int data_sent = FALSE;
    MPI_Status status;

    do {
        if (!outbound_request_in_progress && outbound_queue.size() > 0) {
            outbound_data = outbound_queue.front();
            MPI_Isend(&(outbound_data.data), ONE_MESSAGE, MPI_INT, outbound_data.destination, outbound_data.tag, MPI_COMM_WORLD, &outbound_request);
            outbound_request_in_progress = true;
            data_sent = FALSE;
        }
        if (outbound_request_in_progress) {
            MPI_Test(&outbound_request, &data_sent, &status);
        }
        if (data_sent) {
            outbound_queue.pop();
            outbound_request_in_progress = false;
        }
    } while (!outbound_request_in_progress && outbound_queue.size() > 0);
}


// ***** Initializations *****
void initialize_MPI(int argc, char* argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and process count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);  
}

void initialize_prng() {
	srand(static_cast<unsigned>(time(NULL)));
}


int main(int argc, char** argv) {
    // put command line args in string vector
    std::vector<std::string> args(argv + 1, argv + argc);

    initialize_prng();
    initialize_MPI(argc, argv);

    command_line_args = parse_command_line_args(args);
    validate_command_line_args(command_line_args);

    start_timer();
    //start_logging();

    stop_timer();
    //stop_logging();

    // Shutdown MPI
    MPI_Finalize();
    if (rank == LEADER) {
        printf("Run completed.  Total elapsed time: %'6.2f seconds.  See log files\n", get_overall_elapsed_time());
    }

	return 0;
} 
