#include <cmath>
#include <cstdio>
#include "distance_profile.h"
#include "mean_and_standard_deviation.h"
#include "sliding_dot_product.h"


DoubleArray calculate_cumulative_sum(const DoubleArray& input) {

	double sum = 0.0;

	DoubleArray result;
	result.length = input.length + 1;
	result.data = (double*) calloc(result.length, sizeof(double));
	result.data[0] = sum;
	for (unsigned long i = 0; i < input.length; i++) {
		sum += input.data[i];
		result.data[i+1] = sum;
	}
	return result;
}

DoubleArray square(const DoubleArray& input) {
	
	DoubleArray result;
	result.length = input.length;
	result.data = (double*) calloc(result.length, sizeof(double));
	for (unsigned long i = 0; i < input.length; i++) {
		result.data[i] = input.data[i] * input.data[i];
	}
	return result;
}

DoubleArray normalize(const DoubleArray& input) {
	
    double input_mean;
    double input_standard_deviation;

    compute_mean_and_standard_deviation(input, input_mean, input_standard_deviation); 

    printf("\ninput_mean:  %f\tinput_standard_deviation:  %f\n", input_mean, input_standard_deviation);

	DoubleArray result;
	result.length = input.length;
	result.data = (double*) calloc(result.length, sizeof(double));
	for (unsigned long i = 0; i < input.length; i++) {
		result.data[i] = (input.data[i] - input_mean) / input_standard_deviation;
	}
	return result;
}

DoubleArray calculate_subsequence_sum(const DoubleArray& query_segment, const DoubleArray& time_series, const DoubleArray& cumulative_sum) {

    unsigned long matrix_profile_length = time_series.length - query_segment.length + 1;
	DoubleArray subsequence_sum;
	subsequence_sum.length = matrix_profile_length;	
	subsequence_sum.data = (double*) calloc(subsequence_sum.length, sizeof(double));
	for (unsigned long i = query_segment.length, j = 0; j < subsequence_sum.length; i++, j++) {
		subsequence_sum.data[j] = cumulative_sum.data[i] - cumulative_sum.data[j];
	}
	return subsequence_sum;
}

// MASS from TABLE 2
// Input:  A query_segment (part of the time_series that is window_size in length), and the whole time_series
// Output:  A distance_profile for the query_segment
// This puts the Mueen Similarity Search (MASS) steps from the work_breakdown_structure.txt inside of
// calculate_distance_profile instead of external to it.
DoubleArray calculate_distance_profile(const DoubleArray& query_segment, const DoubleArray& time_series) {

    unsigned long matrix_profile_length = time_series.length - query_segment.length + 1;
	double n = (double) time_series.length;
	double m = (double) query_segment.length;

	// normalize query_seqment
	DoubleArray normalized_query_segment = normalize(query_segment);   // free1
	printf("\nNormalized query segment\n");
    printDoubleArray("normalized_query_segment", normalized_query_segment);

	// calculate sliding_dot_product
    DoubleArray dot_product = sliding_dot_product(normalized_query_segment, time_series);  // free5
    printf("\nCalculated dot product\n");
    printDoubleArray("dot_product", dot_product);
	free(normalized_query_segment.data);  // free1

	// calculate cumulative sum of time_series
	DoubleArray cumulative_sum_time_series = calculate_cumulative_sum(time_series);  // free3
    printf("\nCalculated cumulative sum of time series\n");
    printDoubleArray("cumulative_sum_time_series", cumulative_sum_time_series);

	// calculate cumulative sum of time_series squared
	DoubleArray squared_time_series = square(time_series);  // free2
    printf("\nSquared time_series\n");
    printDoubleArray("squared_time_series", squared_time_series);
	DoubleArray cumulative_sum_time_series_squared = calculate_cumulative_sum(squared_time_series);  // free4
    printf("\nCalculated cumlative sum of time series squared\n");
    printDoubleArray("cumulative_sum_time_series_squared", cumulative_sum_time_series_squared);
	free(squared_time_series.data);  // free2
	
	// calculate subsequence sum of time_series
	DoubleArray subsequence_sum_time_series = calculate_subsequence_sum(query_segment, time_series, cumulative_sum_time_series);  // free6
    printf("\nCalculated subsequence sum of time_series\n");
    printDoubleArray("subsequence_sum_time_series", subsequence_sum_time_series);
	free(cumulative_sum_time_series.data);  // free3

	// calculate subsequence sum of time_series squared
	DoubleArray subsequence_sum_time_series_squared = calculate_subsequence_sum(query_segment, time_series, cumulative_sum_time_series_squared);  // free7
    printf("\nCalculated subsequence sum of time_series squared\n");
    printDoubleArray("subsequence_sum_time_series_squared", subsequence_sum_time_series_squared);
	free(cumulative_sum_time_series_squared.data);  // free4

	// calculate time_series means
	DoubleArray time_series_means;
	time_series_means.length = subsequence_sum_time_series.length;
	time_series_means.data = (double*) calloc(time_series_means.length, sizeof(double));  // free8
	for (unsigned long i = 0; i < time_series_means.length; i++) {
		time_series_means.data[i] = subsequence_sum_time_series.data[i] / m;
	}
    printf("\nCalculated time_series means\n");
    printDoubleArray("time_series_means", time_series_means);

    // calculate time_series means squared
    DoubleArray time_series_means_squared = square(time_series_means); // free11
    printf("\nCalculated time_series means squared\n");
    printDoubleArray("time_series_means_squared", time_series_means_squared);

	// calculate time_series variances
	DoubleArray time_series_variances;
	time_series_variances.length = subsequence_sum_time_series_squared.length;
	time_series_variances.data = (double*) calloc(time_series_variances.length, sizeof(double));  // free9
	for (unsigned long i = 0; i < time_series_variances.length; i++) {
		time_series_variances.data[i] = std::fabs( subsequence_sum_time_series_squared.data[i] / m - time_series_means_squared.data[i] );
	}
    printf("\nCalculated time_series variances\n");
    printDoubleArray("time_series_variances", time_series_variances);

	// calculate time_series standard deviations
	DoubleArray time_series_standard_deviations;
	time_series_standard_deviations.length = time_series_variances.length;
	time_series_standard_deviations.data = (double*) calloc(time_series_standard_deviations.length, sizeof(double));  // free10
	for (unsigned long i = 0; i < time_series_standard_deviations.length; i++) {
		time_series_standard_deviations.data[i] = std::sqrt(time_series_variances.data[i]);
	}	
    printf("\nCalculated time_series standard deviations\n");
    printDoubleArray("time_series_standard_deviations", time_series_standard_deviations);

    // calculate distance profile
    DoubleArray distance_profile;
    distance_profile.length = matrix_profile_length;
    distance_profile.data = (double*) calloc(distance_profile.length, sizeof(double));
	for (unsigned long i = 0; i < distance_profile.length; i++) {
		distance_profile.data[i] = std::sqrt( std::fabs (
								       (subsequence_sum_time_series_squared.data[i] - 2.0 * subsequence_sum_time_series.data[i] * time_series_means.data[i] + m * time_series_means_squared.data[i])
                                       / time_series_variances.data[i]
                                       - 2.0 * dot_product.data[i] / time_series_standard_deviations.data[i]
                                       + m
								   ));
	}

	printf("\nComputed distance_profile\n");
    printDoubleArray("distance_profile", distance_profile);

	// clean up intermediate data
	free(dot_product.data);  // free5
    free(subsequence_sum_time_series.data);  // free6
    free(subsequence_sum_time_series_squared.data);  // free7
    free(time_series_means.data);  // free8
    free(time_series_variances.data);  // free9
    free(time_series_standard_deviations.data);  // free10
    free(time_series_means_squared.data);  // free11

    return distance_profile;
}
