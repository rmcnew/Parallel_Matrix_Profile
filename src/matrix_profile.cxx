#include <mpi.h>
#include <chrono>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <sstream>
#include <string>
#include <vector>


#define FALSE 0
#define TRUE 1
#define LEADER 0
#define LOG_BUFFER_SIZE 1024
#define ONE_MESSAGE 1
#define ONE_MILLION 1000000.0


int rank;
int process_count;    

std::string input_filename;
std::string output_filename;

std::FILE* log_handle = nullptr;
std::FILE* input_handle = nullptr;
std::FILE* output_handle = nullptr;


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

// timing metrics globals
std::chrono::time_point<std::chrono::high_resolution_clock> overall_start;
std::chrono::time_point<std::chrono::high_resolution_clock> overall_stop;


// ***** Command Line Arguments *****
// Print usage help
void print_usage() {
	if (rank == LEADER) {
		printf("\n\nUsage: mpirun -n <PROCESS_COUNT> -f <hostfile> ./matrix_profile -i <INPUT_FILE.CSV> -o <OUTPUT_FILE.CSV\n");
	}
}

// Extract method from command line arg
void parse_command_line_args(std::vector<std::string> args) {    
	for (auto arg = args.begin(); arg != args.end(); arg++) {
        if (*arg == "-h" || *arg == "--help") {
            print_usage();
			MPI_Finalize();
			exit(EXIT_SUCCESS);
        } else if (*arg == "-i") {
    		// get input_filename
			arg++;
            input_filename = *arg;
        } else if (*arg == "-o") {
    		// get output_filename
			arg++;
            output_filename = *arg;
        }
    }
}

// Ensure that seconds_to_run is positive
void validate_command_line_args() {
    bool valid = true;
	// check that input_filename exists and can be read

    // check that output_filename can be opened for writing

	// if invalid, print usage and exit 	
    if (!valid) {
		print_usage();
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    if (rank == LEADER) {
        printf("Running with %d processes\nUsing input_file: %s and output_file: %s\n", process_count, input_filename.c_str(), output_filename.c_str());
    }
}

// ***** Logging *****
void start_logging() {
    std::stringstream filename;
    filename << "process_" << rank << ".log";
    log_handle = fopen((const char*)filename.str().c_str(), "w");
    if (log_handle == NULL) {
        fprintf(stderr, "Error opening %s for writing\n", filename.str().c_str());
        log_handle = stdout;
    }
}

void stop_logging() {
    if (log_handle != stdout) {
        fflush(log_handle);
        fclose(log_handle);
        log_handle = stdout;
    }
}

double get_elapsed_time() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - overall_start).count() / ONE_MILLION;
}

void log(const char* format, ...) {
    char log_buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(log_buffer, LOG_BUFFER_SIZE, format, args);
    va_end(args);

    double elapsed_time = get_elapsed_time();
    fprintf(log_handle, "%4.6f [Process %d] %s\n", elapsed_time, rank, log_buffer);
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
	srandom(static_cast<unsigned>(time(NULL)));
}

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);

    initialize_prng();
    initialize_MPI(argc, argv);

    parse_command_line_args(args);
    validate_command_line_args();

    overall_start = std::chrono::high_resolution_clock::now();
    //start_logging();

    overall_stop = std::chrono::high_resolution_clock::now();
    double overall_elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(overall_stop - overall_start).count() / ONE_MILLION;

    //stop_logging();

    // Shutdown MPI
    MPI_Finalize();
    if (rank == LEADER) {
        printf("Run completed.  Total elapsed time: %'6.2f seconds.  See log files\n", overall_elapsed_time);
    }


	return 0;
} 
