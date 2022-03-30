#include <cmath>
#include <cstdio>
#include "distance_profile.h"
#include "mean_and_standard_deviation.h"
#include "sliding_dot_product.h"

// MASS from TABLE 2
// Input:  A query_segment (part of the time_series that is window_size in length), and the whole time_series
// Output:  A distance_profile for the query_segment
// This puts the Mueen Similarity Search (MASS) steps from the work_breakdown_structure.txt inside of
// calculate_distance_profile instead of external to it.
DoubleArray calculate_distance_profile(const DoubleArray& query_segment, const DoubleArray& time_series) {

    double query_segment_mean;
    double query_segment_standard_deviation;
    double time_series_mean;
    double time_series_standard_deviation;

    compute_mean_and_standard_deviation(
        query_segment, time_series, 
        query_segment_mean, query_segment_standard_deviation, 
        time_series_mean, time_series_standard_deviation); 

    //printf("query_segment_mean:  %f\nquery_segment_standard_deviation:  %f\ntime_series_mean:  %f\ntime_series_standard_deviation:  %f\n", query_segment_mean, query_segment_standard_deviation, time_series_mean, time_series_standard_deviation);

    DoubleArray dot_product = sliding_dot_product(query_segment, time_series);

    //printDoubleArray("dot_product", dot_product);

    unsigned long matrix_profile_length = time_series.length - query_segment.length + 1;
    printf("matrix_profile_length: %lu\n", matrix_profile_length);
    
    DoubleArray distance_profile;
    distance_profile.length = matrix_profile_length;
    distance_profile.data = (double*) calloc(distance_profile.length, sizeof(double));

    // RSM:  I think the calculation is off.  Will use another library to verify the sliding dot product and distance profile calculations for known input data
    for (unsigned long i = 0; i < distance_profile.length; i++) {
        distance_profile.data[i] = std::sqrt(2 * query_segment.length * (1 - ((dot_product.data[i] - query_segment.length * query_segment_mean * time_series_mean) / (query_segment.length * query_segment_standard_deviation * time_series_standard_deviation))));
    }

	printf("\nComputed distance_profile\n");
    printDoubleArray("distance_profile", distance_profile);

	// clean up dot_product
	free(dot_product.data);

    return distance_profile;
}
