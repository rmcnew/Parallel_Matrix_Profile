
#include "mean_and_standard_deviation.h"
#include "types.h"

void compute_mean_and_standard_deviation(
        const DoubleArray& query_segment, const DoubleArray& time_series,               // input values
        double& query_segment_mean, double& query_segment_standard_deviation,           // output values
        double& time_series_window_mean, double& time_series_window_standard_deviation  // output values
        ) {

    // The paper “Searching and Mining Trillions of Time Series Subsequences under Dynamic Time Warping” shows a fast way to do this.  
    // This is referenced in TABLE 2 in the Matrix Profile 1 paper (reference number 22).
    
    // the paper recommends cacheing partial sums to speed up the mean and standard deviation calculations
    // We can just implement normal mean and standard deviation calculations.
    // First we need to make it work correctly, then we can see about making it faster.

    // there is some overlap in how means and standard deviations are calculated so we can
    // have some optimization by avoiding computing the same values twice
    query_segment_mean = 0.0;
    query_segment_standard_deviation = 0.0;
    time_series_window_mean = 0.0;
    time_series_window_standard_deviation = 0.0;
}
