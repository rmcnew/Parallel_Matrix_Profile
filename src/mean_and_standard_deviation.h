#ifndef GROUP_010_MEAN_AND_STANDARD_DEVIATION_H
#define GROUP_010_MEAN_AND_STANDARD_DEVIATION_H

#include "types.h"

void compute_mean_and_standard_deviation(
        const DoubleArray& query_segment, const DoubleArray& time_series,      // input values
        double& query_segment_mean, double& query_segment_standard_deviation,  // output values
        double& time_series_mean, double& time_series_standard_deviation);     // output values
        

#endif // GROUP_010_MEAN_AND_STANDARD_DEVIATION_H

