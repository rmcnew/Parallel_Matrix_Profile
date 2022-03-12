#include <mpi.h>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>
#include "log.h"
#include "read_time_series_csv.h"
#include "timing.h"

#define FALSE 0
#define TRUE 1
#define LEADER 0
#define ONE_MESSAGE 1


int rank;
int process_count;    

std::string input_file;
std::string output_file;

std::string window_size_str;
int window_size = 10;

int input_column = 1;

TimeSeries time_series;

double* distance_profile = nullptr;
double* matrix_profile = nullptr;


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



// ***** Command Line Arguments *****
// Print usage help
void print_usage() {
	if (rank == LEADER) {
		printf("\n\nUsage: mpirun -n <PROCESS_COUNT> -f <hostfile> ./matrix_profile --input-file <INPUT_FILE.CSV> --output-file <OUTPUT_FILE.CSV> [--window-size WINDOW_SIZE] [--input-column INPUT_COLUMN]\n");
	}
}


void parse_command_line_args(std::vector<std::string> args) {    
	for (auto arg = args.begin(); arg != args.end(); arg++) {
        if (*arg == "-h" || *arg == "--help") {
            print_usage();
			MPI_Finalize();
			exit(EXIT_SUCCESS);
        } else if (*arg == "--input-file") { 
			arg++;
            input_file = *arg;
        } else if (*arg == "--output-file") { 
			arg++;
            output_file = *arg;
        } else if (*arg == "--window-size") {
            arg++;
            window_size_str = *arg;
        } else if (*arg == "--input-column") {
            arg++;
            std::string input_column_str = *arg;
            input_column = std::stoi(input_column_str);
        }
    }
}


void validate_command_line_args() {
    bool valid = true;
	// check that input_file exists and can be read
    
    // check that output_file can be opened for writing

    // if present, window_size must be positive

    // if present, input_column must be positive

	// if invalid, print usage and exit 	
    if (!valid) {
		print_usage();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    if (rank == LEADER) {
        printf("Running with %d processes\nUsing input_file: %s and output_file: %s\nUsing window_size: %d and input_column: %d\n", process_count, input_file.c_str(), output_file.c_str(), window_size, input_column);
    }
}


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
    std::vector<std::string> args(argv + 1, argv + argc);

    initialize_prng();
    initialize_MPI(argc, argv);

    parse_command_line_args(args);
    validate_command_line_args();

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
