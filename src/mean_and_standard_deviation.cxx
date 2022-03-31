#include <cmath>
#include "mean_and_standard_deviation.h"
#include "types.h"


long double calculate_mean(const DoubleArray& double_array) {

	long double mean = 0.0;

	for (unsigned long i = 0; i < double_array.length; i++) {
		mean += (double_array.data[i] - mean) / (i + 1);
	}
	return mean;
}


long double calculate_standard_deviation (const DoubleArray& double_array) { 

	const long double mean = calculate_mean(double_array);

	long double variance = 0.0 ;

	for (unsigned long i = 0; i < double_array.length; i++) {
		const long double delta = (double_array.data[i] - mean);
		variance += (delta * delta);
	}

	return std::sqrt( (variance / (double)double_array.length) );
}




void compute_mean_and_standard_deviation(
        const DoubleArray& query_segment,          // input 
        double& query_segment_mean,                // output values 
        double& query_segment_standard_deviation) {

    // The paper “Searching and Mining Trillions of Time Series Subsequences under Dynamic Time Warping” shows a fast way to do this.  
    // This is referenced in TABLE 2 in the Matrix Profile 1 paper (reference number 22).
    
    // the paper recommends cacheing partial sums to speed up the mean and standard deviation calculations
    // We can just implement normal mean and standard deviation calculations.
    // First we need to make it work correctly, then we can see about making it faster.
    query_segment_mean = calculate_mean(query_segment);
    query_segment_standard_deviation = calculate_standard_deviation(query_segment);
}
