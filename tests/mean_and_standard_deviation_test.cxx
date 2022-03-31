#include <gtest/gtest.h>
#include "mean_and_standard_deviation.h"


TEST(MeanAndStandardDeviationTest, test_mean_and_standard_deviation) {
    
    /* Test for mean_and_standard_deviation:

    void compute_mean_and_standard_deviation(
            const DoubleArray& query_segment,          // input values
            double& query_segment_mean,                // output values
            double& query_segment_standard_deviation);   

    */

    // create test query_segment and time_series
    DoubleArray qs;
    qs.length = 9;
    qs.data = (double*) calloc(qs.length, sizeof(double));
    qs.data[0] = 11.0;
    qs.data[1] = 22.0;
    qs.data[2] = 33.0;
    qs.data[3] = 44.0;
    qs.data[4] = 55.0;
    qs.data[5] = 66.0;
    qs.data[6] = 77.0;
    qs.data[7] = 88.0;
    qs.data[8] = 99.0;

    const double expected_qs_mean = 55.0;
    const double expected_qs_standard_deviation = 28.401877872187722;

	double qs_mean = 0.0;
	double qs_standard_deviation = 0.0;

    // calculate means and standard deviations
	compute_mean_and_standard_deviation(qs, qs_mean, qs_standard_deviation); 

    // compare with pre-computed values    
	EXPECT_DOUBLE_EQ(expected_qs_mean, qs_mean);
	EXPECT_DOUBLE_EQ(expected_qs_standard_deviation, qs_standard_deviation);

    // free allocated memory
    free(qs.data);
}

