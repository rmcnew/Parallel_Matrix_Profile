#include <cstdarg>
#include <cstdio>
#include <sstream>
#include "log.h"
#include "timing.h"

#define LOG_BUFFER_SIZE 1024

std::FILE* log_handle = nullptr;
extern int rank;


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


void log(const char* format, ...) {
    char log_buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(log_buffer, LOG_BUFFER_SIZE, format, args);
    va_end(args);

    double elapsed_time = get_elapsed_time();
    fprintf(log_handle, "%4.6f [Process %d] %s\n", elapsed_time, rank, log_buffer);
}

