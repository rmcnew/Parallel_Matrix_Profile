#include <cfloat>
#include <cstdio>
#include "distance_profile.h"
#include "sliding_dot_product.h"
#include "stamp.h"

extern int rank;
extern int process_count;


void printMatrixProfile(const std::string& name, const MatrixProfile& matrix_profile) {
    printf("%s data:  ", name.c_str());
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        printf("%e\t", matrix_profile.data[i]);
    }
    printf("\n%s indices:  ", name.c_str());
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        printf("%lu\t", matrix_profile.index[i]);
    }
    printf("\n%s length: %lu\n", name.c_str(), matrix_profile.length);
}


// Element-wise minimum needed for STAMP
void elementwise_minimum(MatrixProfile& matrix_profile, const LongDoubleArray& distance_profile, const unsigned long& index, const unsigned long& exclusion_radius) {
    unsigned long exclusion_start = index - exclusion_radius;
    unsigned long exclusion_stop = index + exclusion_radius;
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        if (i < exclusion_start || i > exclusion_stop) {
            if (matrix_profile.data[i] > distance_profile.data[i]) {
                matrix_profile.data[i] = distance_profile.data[i];
                matrix_profile.index[i] = i;  // is this correct?
                //printMatrixProfile("updated matrix_profile", matrix_profile);
            }
        }
    }
}


// STAMP from TABLE 3
// Input:  time_series and window_size
// Output:  matrix_profile and matrix_profile_index
MatrixProfile stamp(const LongDoubleArray& time_series, const int& window_size, const unsigned long& exclusion_radius) {

    // Step 1:  time_series.length (called 'n' in the paper)) is part of time_series
    MatrixProfile matrix_profile;
    matrix_profile.length = time_series.length - window_size + 1;

    // Step 2
    // Initialize local matrix profile and matrix profile index
    matrix_profile.data = (long double*) calloc(matrix_profile.length, sizeof(long double));
    matrix_profile.index = (unsigned long*) calloc(matrix_profile.length, sizeof(unsigned long));
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        matrix_profile.data[i] = DBL_MAX;
        matrix_profile.index[i] = 0;
    }
    printf("matrix_profile initialized\n");

    // Step 3:  Each process handles its time series segment indices
    unsigned long factor = matrix_profile.length / process_count;
    unsigned long start_index = rank * factor;
    unsigned long stop_index = (rank == process_count - 1) ? (matrix_profile.length - 1) : (start_index + factor);

    for (unsigned long index = start_index; index < stop_index; index++) {
        printf("Calculating distance profile for index: %lu\n", index);
        LongDoubleArray query_segment;
        query_segment.data = &(time_series.data[index]);
        query_segment.length = window_size;
        LongDoubleArray distance_profile = calculate_distance_profile(query_segment, time_series);
        //printLongDoubleArray("distance_profile", distance_profile);
        elementwise_minimum(matrix_profile, distance_profile, index, exclusion_radius);
    }
    return matrix_profile;
}
