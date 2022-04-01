#include <cmath>
#include <cstdio>
#include "distance_profile.h"
#include "mean_and_standard_deviation.h"
#include "sliding_dot_product.h"

LongDoubleArray to_LongDoubleArray(const DoubleArray& in) {

    LongDoubleArray out;
    out.length = in.length;
    out.data = (long double*) calloc(out.length, sizeof(long double));
    for (unsigned long i = 0; i < out.length; i++) {
        out.data[i] = (long double)in.data[i];
    }
    return out;
}

DoubleArray to_DoubleArray(const LongDoubleArray& in) {

    DoubleArray out;
    out.length = in.length;
    out.data = (double*) calloc(out.length, sizeof(double));
    for (unsigned long i = 0; i < out.length; i++) {
        out.data[i] = (double)in.data[i];  // loss of precision
    }
    return out;
}


LongDoubleArray calculate_cumulative_sum(const LongDoubleArray& input) {

	double sum = 0.0;

	LongDoubleArray result;
	result.length = input.length + 1;
	result.data = (long double*) calloc(result.length, sizeof(long double));
	result.data[0] = sum;
	for (unsigned long i = 0; i < input.length; i++) {
		sum += input.data[i];
		result.data[i+1] = sum;
	}
	return result;
}

LongDoubleArray square(const LongDoubleArray& input) {
	
	LongDoubleArray result;
	result.length = input.length;
	result.data = (long double*) calloc(result.length, sizeof(long double));
	for (unsigned long i = 0; i < input.length; i++) {
		result.data[i] = input.data[i] * input.data[i];
	}
	return result;
}

LongDoubleArray normalize(const LongDoubleArray& input) {
	
    long double input_mean;
    long double input_standard_deviation;

    compute_mean_and_standard_deviation(input, input_mean, input_standard_deviation); 

    //printf("\ninput_mean:  %Lf\tinput_standard_deviation:  %Lf\n", input_mean, input_standard_deviation);

	LongDoubleArray result;
	result.length = input.length;
	result.data = (long double*) calloc(result.length, sizeof(long double));
	for (unsigned long i = 0; i < input.length; i++) {
		result.data[i] = (input.data[i] - input_mean) / input_standard_deviation;
	}
	return result;
}

LongDoubleArray calculate_subsequence_sum(const LongDoubleArray& query_segment, const LongDoubleArray& time_series, const LongDoubleArray& cumulative_sum) {

    unsigned long matrix_profile_length = time_series.length - query_segment.length + 1;
	LongDoubleArray subsequence_sum;
	subsequence_sum.length = matrix_profile_length;	
	subsequence_sum.data = (long double*) calloc(subsequence_sum.length, sizeof(long double));
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
LongDoubleArray calculate_distance_profile(const LongDoubleArray& query_segment, const LongDoubleArray& time_series) {

    unsigned long matrix_profile_length = time_series.length - query_segment.length + 1;
	long double n = (long double) time_series.length;
	long double m = (long double) query_segment.length;

	// normalize query_seqment
	LongDoubleArray normalized_query_segment = normalize(query_segment);   // free1
	//printf("\nNormalized query segment\n");
    //printLongDoubleArray("normalized_query_segment", normalized_query_segment);

	// calculate sliding_dot_product
    LongDoubleArray dot_product = sliding_dot_product(normalized_query_segment, time_series);  // free2
    //printf("\nCalculated dot product\n");
    //printLongDoubleArray("dot_product", dot_product);

	// calculate cumulative sum of time_series
	LongDoubleArray cumulative_sum_time_series = calculate_cumulative_sum(time_series);  // free3
    //printf("\nCalculated cumulative sum of time series\n");
    //printLongDoubleArray("cumulative_sum_time_series", cumulative_sum_time_series);

	// calculate cumulative sum of time_series squared
	LongDoubleArray squared_time_series = square(time_series);  // free4
    //printf("\nSquared time_series\n");
    //printLongDoubleArray("squared_time_series", squared_time_series);
	LongDoubleArray cumulative_sum_time_series_squared = calculate_cumulative_sum(squared_time_series);  // free5
    //printf("\nCalculated cumlative sum of time series squared\n");
    //printLongDoubleArray("cumulative_sum_time_series_squared", cumulative_sum_time_series_squared);
	
	// calculate subsequence sum of time_series
	LongDoubleArray subsequence_sum_time_series = calculate_subsequence_sum(query_segment, time_series, cumulative_sum_time_series);  // free6
    //printf("\nCalculated subsequence sum of time_series\n");
    //printLongDoubleArray("subsequence_sum_time_series", subsequence_sum_time_series);

	// calculate subsequence sum of time_series squared
	LongDoubleArray subsequence_sum_time_series_squared = calculate_subsequence_sum(query_segment, time_series, cumulative_sum_time_series_squared);  // free7
    //printf("\nCalculated subsequence sum of time_series squared\n");
    //printLongDoubleArray("subsequence_sum_time_series_squared", subsequence_sum_time_series_squared);

	// calculate time_series means
	LongDoubleArray time_series_means;
	time_series_means.length = subsequence_sum_time_series.length;
	time_series_means.data = (long double*) calloc(time_series_means.length, sizeof(long double));  // free8
	for (unsigned long i = 0; i < time_series_means.length; i++) {
		time_series_means.data[i] = subsequence_sum_time_series.data[i] / m;
	}
    //printf("\nCalculated time_series means\n");
    //printLongDoubleArray("time_series_means", time_series_means);

    // calculate time_series means squared
    LongDoubleArray time_series_means_squared = square(time_series_means); // free11
    //printf("\nCalculated time_series means squared\n");
    //printLongDoubleArray("time_series_means_squared", time_series_means_squared);

	// calculate time_series variances
	LongDoubleArray time_series_variances;
	time_series_variances.length = subsequence_sum_time_series_squared.length;
	time_series_variances.data = (long double*) calloc(time_series_variances.length, sizeof(long double));  // free9
	for (unsigned long i = 0; i < time_series_variances.length; i++) {
		time_series_variances.data[i] = std::fabs( subsequence_sum_time_series_squared.data[i] / m - time_series_means_squared.data[i] );
	}
    //printf("\nCalculated time_series variances\n");
    //printLongDoubleArray("time_series_variances", time_series_variances);

	// calculate time_series standard deviations
	LongDoubleArray time_series_standard_deviations;
	time_series_standard_deviations.length = time_series_variances.length;
	time_series_standard_deviations.data = (long double*) calloc(time_series_standard_deviations.length, sizeof(long double));  // free10
	for (unsigned long i = 0; i < time_series_standard_deviations.length; i++) {
		time_series_standard_deviations.data[i] = std::sqrt(time_series_variances.data[i]);
	}	
    //printf("\nCalculated time_series standard deviations\n");
    //printLongDoubleArray("time_series_standard_deviations", time_series_standard_deviations);

    // calculate distance profile
    LongDoubleArray distance_profile;
    distance_profile.length = matrix_profile_length;
    distance_profile.data = (long double*) calloc(distance_profile.length, sizeof(long double));  // return value, do not free here
	for (unsigned long i = 0; i < distance_profile.length; i++) {
        long double first = subsequence_sum_time_series_squared.data[i] - 2.0L * subsequence_sum_time_series.data[i] * time_series_means.data[i] + m * time_series_means_squared.data[i];
        long double second = time_series_variances.data[i];
        long double third = 2.0L * dot_product.data[i] / time_series_standard_deviations.data[i];
        long double d_squared = std::fabs ( first / second - third + m);
        long double d = std::sqrt(d_squared);
        distance_profile.data[i] = d;
	}

	//printf("\n\nComputed distance_profile\n");
    //printLongDoubleArray("distance_profile", distance_profile);

	// clean up intermediate data
	free(normalized_query_segment.data);  // free1
	free(dot_product.data);  // free2
	free(cumulative_sum_time_series.data);  // free3
	free(squared_time_series.data);  // free4
	free(cumulative_sum_time_series_squared.data);  // free5
    free(subsequence_sum_time_series.data);  // free6
    free(subsequence_sum_time_series_squared.data);  // free7
    free(time_series_means.data);  // free8
    free(time_series_variances.data);  // free9
    free(time_series_standard_deviations.data);  // free10
    free(time_series_means_squared.data);  // free11

    return distance_profile;
}
