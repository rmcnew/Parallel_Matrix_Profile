#include <algorithm>
#include <cstdio>
#include <limits>
#include "distance_profile.h"
#include "sliding_dot_product.h"
#include "stamp.h"

extern int rank;
extern int process_count;


void printMatrixProfile(const std::string& name, const MatrixProfile& mp) {
    printf("%s data:  ", name.c_str());
    for (unsigned long i = 0; i < mp.length; i++) {
        printf("%Le\t", mp.data[i]);
    }
    printf("\n%s indices:  ", name.c_str());
    for (unsigned long i = 0; i < mp.length; i++) {
        printf("%lu\t", mp.index[i]);
    }
    printf("\n");
    //printf("\n%s length: %lu\n", name.c_str(), mp.length);
}

unsigned long argmin(const LongDoubleArray& dp) {
	long double minimum_seen = (long double)std::numeric_limits<double>::max();
	unsigned long minimum_index = 0;

	for (unsigned long i = 0; i < dp.length; i++) {
		if (dp.data[i] < minimum_seen) {
			minimum_seen = dp.data[i];
			minimum_index = i;
		}
	}
    return minimum_index;
}

void apply_exclusion_zone(LongDoubleArray& distance_profile, const unsigned long& index, const unsigned long& exclusion_radius) {
    unsigned long exclusion_start = (unsigned long) std::max(((long long)index - (long long)exclusion_radius), (long long)0);
    unsigned long exclusion_stop = std::min((index + exclusion_radius), (distance_profile.length-1));

	for (unsigned long i = exclusion_start; i <= exclusion_stop; i++) {
        distance_profile.data[i] = (long double)std::numeric_limits<double>::max();
	}
}


// Element-wise minimum needed for STAMP
void elementwise_minimum(MatrixProfile& mp, const LongDoubleArray& distance_profile, const unsigned long& index) {
	unsigned long index_to_update = argmin(distance_profile);
    long double value = distance_profile.data[index_to_update];
    if (value < (long double)std::numeric_limits<double>::max()) {
        mp.data[index] = distance_profile.data[index_to_update];
        mp.index[index] = index_to_update;	
		//printMatrixProfile("updated matrix_profile", mp);
    }
}


// STAMP from TABLE 3
// Input:  time_series and window_size
// Output:  matrix_profile and matrix_profile_index
MatrixProfile stamp(const LongDoubleArray& time_series, const int& window_size, const unsigned long& exclusion_radius) {

    // Step 1:  time_series.length (called 'n' in the paper)) is part of time_series

    // Step 2
    // Initialize local matrix profile and matrix profile index
    MatrixProfile matrix_profile;
    matrix_profile.length = time_series.length - window_size + 1;
    matrix_profile.data = (long double*) calloc(matrix_profile.length, sizeof(long double));
    matrix_profile.index = (unsigned long*) calloc(matrix_profile.length, sizeof(unsigned long));
    for (unsigned long i = 0; i < matrix_profile.length; i++) {
        matrix_profile.data[i] = (long double)std::numeric_limits<double>::max();
        matrix_profile.index[i] = 0;
    }
    //printMatrixProfile("matrix_profile initialized", matrix_profile);

    // Step 3:  Each process handles its time series segment indices
    unsigned long factor = matrix_profile.length / process_count;
    unsigned long start_index = rank * factor;
    unsigned long stop_index = (rank == process_count - 1) ? matrix_profile.length : (start_index + factor);

    for (unsigned long index = start_index; index < stop_index; index++) {
        //printf("\n====================\nCalculating distance profile for index: %lu\n", index);
        LongDoubleArray query_segment;
        query_segment.data = &(time_series.data[index]);
        query_segment.length = window_size;
        LongDoubleArray distance_profile = calculate_distance_profile(query_segment, time_series);
        //printLongDoubleArray("distance_profile", distance_profile);
		//printf("Applying exclusion zone\n");
		apply_exclusion_zone(distance_profile, index, exclusion_radius);
        //printLongDoubleArray("excluded distance_profile", distance_profile);
		//printf("Performing elementwise_minimum\n");
        elementwise_minimum(matrix_profile, distance_profile, index);
        //printMatrixProfile("updated matrix_profile", matrix_profile);
        free(distance_profile.data);
    }
    return matrix_profile;
}
