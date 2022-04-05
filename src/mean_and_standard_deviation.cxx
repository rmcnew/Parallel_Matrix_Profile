#include <cmath>
#include "mean_and_standard_deviation.h"
#include "types.h"


long double calculate_mean(const LongDoubleArray& input) {

	long double mean = 0.0;

	for (unsigned long i = 0; i < input.length; i++) {
		mean += (input.data[i] - mean) / (i + 1);
	}
	return mean;
}


long double calculate_standard_deviation (const LongDoubleArray& input) { 

	const long double mean = calculate_mean(input);

	long double variance = 0.0 ;

	for (unsigned long i = 0; i < input.length; i++) {
		const long double delta = (input.data[i] - mean);
		variance += (delta * delta);
	}

	return std::sqrt( (variance / (long double)input.length) );
}




void compute_mean_and_standard_deviation(
        const LongDoubleArray& query_segment,          // input 
        long double& query_segment_mean,                // output values 
        long double& query_segment_standard_deviation) {

    // The paper “Searching and Mining Trillions of Time Series Subsequences under Dynamic Time Warping” shows a fast way to do this.  
    // This is referenced in TABLE 2 in the Matrix Profile 1 paper (reference number 22).
    
    // the paper recommends cacheing partial sums to speed up the mean and standard deviation calculations
    // We can just implement normal mean and standard deviation calculations.
    // First we need to make it work correctly, then we can see about making it faster.
    query_segment_mean = calculate_mean(query_segment);
    query_segment_standard_deviation = calculate_standard_deviation(query_segment);
}
