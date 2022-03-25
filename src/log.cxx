#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <sstream>
#include "log.h"
#include "timing.h"

#define LOG_BUFFER_SIZE 1024

std::string log_filename;
std::FILE* log_handle = nullptr;
extern int rank;


#ifdef _WIN32
#include <windows.h>    // GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h>     // readlink
#endif

std::filesystem::path get_exe_path() {
#ifdef _WIN32
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    std::wstring path_wstr(path); 
    std::string path_str;
    std::transform(  // truncating conversion
        wide.begin(), 
        wide.end(), 
        std::back_inserter(str), 
        [] (wchar_t c) { return (char)c; });
    std::filesystem::path exe_path(path_str);
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    std::filesystem::path exe_path(std::string(result, (count > 0) ? count : 0));
#endif
    return exe_path.parent_path();
} 



// ***** Logging *****
std::string get_log_filename() {
    if (log_filename.empty()) {
        std::stringstream filename;
        filename << "process_" << rank << ".log";
        std::filesystem::path log_file = get_exe_path() / filename.str();
        log_filename = log_file.string();
    }
	return log_filename;
}


void start_logging() {
    get_log_filename();
    log_handle = fopen((const char*)log_filename.c_str(), "w");
    if (log_handle == NULL) {
        fprintf(stderr, "Error opening %s for writing\n", log_filename.c_str());
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
    fprintf(log_handle, "%4.6f [Process_%d] %s\n", elapsed_time, rank, log_buffer);
}

