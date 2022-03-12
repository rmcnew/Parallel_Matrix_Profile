
#include <chrono>
#include "timing.h"

#define ONE_MILLION 1000000.0

// timing metrics globals
std::chrono::time_point<std::chrono::high_resolution_clock> overall_start;
std::chrono::time_point<std::chrono::high_resolution_clock> overall_stop;


void start_timer() {
    overall_start = std::chrono::high_resolution_clock::now();
}

void stop_timer() {
    overall_stop = std::chrono::high_resolution_clock::now();
}

double get_elapsed_time() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - overall_start).count() / ONE_MILLION;
}

double get_overall_elapsed_time() {
    double overall_elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(overall_stop - overall_start).count() / ONE_MILLION;
    return overall_elapsed_time;
}
