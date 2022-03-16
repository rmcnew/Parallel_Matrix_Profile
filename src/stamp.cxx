#include "distance_profile.h"
#include "stamp.h"

extern int rank;
extern int process_count;

// Element-wise minimum needed for STAMP
void elementwise_minimum(MatrixProfile& matrix_profile, const DoubleArray& distance_profile, unsigned long index) {
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        if (i != index) {
            if (matrix_profile.data[i] > distance_profile.data[i]) {
                matrix_profile.data[i] = distance_profile.data[i];
                matrix_profile.index[i] = i;  // is this correct?
            }
        }
    }
}


// STAMP from TABLE 3
// Input:  time_series and window_size
// Output:  matrix_profile and matrix_profile_index
void stamp(DoubleArray time_series, int window_size, MatrixProfile& matrix_profile) {

    // Step 1
    // time_series.length = length(time_series)  // called 'n' in the paper

    // Step 2
    // Initialize local matrix profile and matrix profile index
    // matrix_profile.data = (double*) calloc(matrix_profile.length, sizeof(double));
    // matrix_profile.index = (unsigned long*) calloc(matrix_profile.length, sizeof(unsigned long));
    // for (unsigned long i = 0; i < matrix_profile.length; i++) {
    //     matrix_profile.data[i] = DBL_MAX;
    //     matrix_profile.index[i] = 0;
    // }

    // Step 3:  Each process handles its time series segment indices
    // unsigned long factor = matrix_profile.length / process_count;
    // unsigned long start_index = rank * factor;
    // unsigned long stop_index = (rank == process_count - 1) ? (matrix_profile.length - 1) : (start_index + factor);
    // for (unsigned long index = start_index; index < stop_index; index++) {
    //     DoubleArray query_segment;
    //     query_segment.data = time_series.data[index];
    //     query_segment.length = window_size;
    //     DoubleArray distance_profile = calculate_distance_profile(query_segment, time_series);
    //	   elementwise_minimum(matrix_profile, distance_profile, index);
    // }
}
