#include <complex>
#include <cstdint>
#include <cstdlib>

#include "sliding_dot_product.h"
#include "types.h"

ComplexArray elementwise_multiply(const ComplexArray& transformed_query_segment, const ComplexArray& transformed_time_series) {
    ComplexArray result;

    //result.length = 2*time_series_length;
    //result.data = (complex<double>*) calloc(result.length, sizeof(complex<double>));
    //for (unsigned long j = 0; j < result.length; j++) {
    //	result = transformed_query_segment[j] * transformed_time_series[j];
    //}

    return result;
}


// This is from TABLE 1 in the Matrix Profile 1 paper
// Input:  A query_segment (part of the time_series that is window_size in length), and the whole time_series
// Output:  The dot product between the query_segment and all subsequences of the time_series
DoubleArray sliding_dot_product(const DoubleArray& query_segment, const DoubleArray& time_series) {
    DoubleArray result;

    // Step 1
    // unsigned long time_series_length = length(time_series)  // called 'n' in the paper
    // unsigned long query_segment_length = length(query_segment)  // called 'm' in the paper
    // unsigned long matrix_profile_length = time_series_length - query_segment_length + 1;

    // Step 2
    // double* appended_time_series = copy time_series and append n zeros

    // Step 3
    // double* reversed_query_segment = reverse(query_segment)

    // Step 4
    // double* appended_query_segment = copy reversed_query_segment and append (2*time_series_length - query_segment_length) zeros

    // Step 5
    // complex* transformed_query_segment = fast_fourier_transform(appended_query_segment)
    // complex* transformed_time_series = fast_fourier_transform(appended_time_series)

    // Step 6
    // complex transformed_dot_product = elementwise_multiply(transformed_query_segment, transformed_time_series)
    // double* dot_product = inverse_fast_fourier_transform(transformed_dot_product)

    // Step 7
    // return dot_product
    return result;
}

// The fast_fourier_transform and inverse_fast_fourier_transform will need to come from an external library (FFTW3).
