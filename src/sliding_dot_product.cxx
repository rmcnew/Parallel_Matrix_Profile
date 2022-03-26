#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "fourier_transform.h"
#include "sliding_dot_product.h"
#include "types.h"

// debugging helper functions
void printDoubleArray(std::string name, const DoubleArray& double_array) {
    printf("%s:  ", name.c_str());
    for (unsigned long i = 0; i < double_array.length; i++) {
        printf("%9.3f\t", double_array.data[i]);
    }
    printf("\n");
    printf("%s length: %lu\n", name.c_str(), double_array.length);
}

void printComplexArray(std::string name, const ComplexArray& complex_array) {
    printf("%s:  ", name.c_str());
    for (unsigned long i = 0; i < complex_array.length; i++) {
        printf("(%9.3f, %9.3f)\t", complex_array.data[i].real(), complex_array.data[i].imag());
    }
    printf("\n");
    printf("%s length: %lu\n", name.c_str(), complex_array.length);
}


ComplexArray elementwise_multiply(const ComplexArray& transformed_time_series, const ComplexArray& transformed_query_segment) {

    ComplexArray result;
    
    result.length = transformed_time_series.length;
    result.data = (std::complex<double>*) calloc(result.length, sizeof(std::complex<double>));
    for (unsigned long i = 0; i < result.length; i++) {
        result.data[i] = transformed_time_series.data[i] * transformed_query_segment.data[i];
    }

    return result;
}

// This is from TABLE 1 in the Matrix Profile 1 paper
// Input:  A query_segment (part of the time_series that is window_size in length), and the whole time_series
// Output:  The dot product between the query_segment and all subsequences of the time_series
DoubleArray sliding_dot_product(const DoubleArray& query_segment, const DoubleArray& time_series) {

    // Step 1:  Get length of time_series and query_segment
    unsigned long time_series_length = time_series.length;      // called 'n' in the paper
    unsigned long query_segment_length = query_segment.length;  // called 'm' in the paper

    printf("Step 1:  Get length of time_series and query_segment\n");
    printDoubleArray("time_series", time_series);
    printDoubleArray("query_segment", query_segment);

    // Step 2: Append time_series with time_series.length zeros to get appended_time_series
    DoubleArray appended_time_series;
    appended_time_series.length = 2*time_series.length;
    appended_time_series.data = (double*) calloc(appended_time_series.length, sizeof(double));
    for (unsigned long i = 0; i < time_series.length; i++) {
        appended_time_series.data[i] = time_series.data[i];
    }

    printf("\nStep 2: Append time_series with time_series.length zeros to get appended_time_series\n");
    printDoubleArray("appended_time_series", appended_time_series);


    // Step 3:  Reverse query_segment to get reversed_query_segment
    DoubleArray reversed_query_segment;
    reversed_query_segment.length = query_segment.length;
    reversed_query_segment.data = (double*) calloc(reversed_query_segment.length, sizeof(double));
    for (unsigned long i = 0, j = query_segment.length - 1; i < query_segment.length; i++, j--) {
        reversed_query_segment.data[i] = query_segment.data[j];
    }

    printf("\nStep 3:  Reverse query_segment to get reversed_query_segment\n");
    printDoubleArray("reversed_query_segment", reversed_query_segment);

    // Step 4: Append reversed_query_segment with (2*time_series.length - query_segment.length) zeros to get appended_query_segment
    DoubleArray appended_query_segment;
    appended_query_segment.length = reversed_query_segment.length + (2*time_series.length - query_segment.length);
    appended_query_segment.data = (double*) calloc(appended_query_segment.length, sizeof(double));
    for (unsigned long i = 0; i < reversed_query_segment.length; i++) {
        appended_query_segment.data[i] = reversed_query_segment.data[i];
    }

    printf("\nStep 4: Append reversed_query_segment with (2*time_series.length - query_segment.length) zeros to get appended_query_segment\n");
    printDoubleArray("appended_query_segment", appended_query_segment);

    // Step 5:  Fourier transforms for appended_time_series and appended_query_segment to get transformed_time_series and transformed_query_segment
    ComplexArray transformed_time_series = fast_fourier_transform(appended_time_series);
    ComplexArray transformed_query_segment = fast_fourier_transform(appended_query_segment);

    printf("\nStep 5:  Fourier transforms for appended_time_series and appended_query_segment to get transformed_time_series and transformed_query_segment\n");
    printComplexArray("transformed_time_series", transformed_time_series);
    printComplexArray("transformed_query_segment", transformed_query_segment);

    // Step 6a:  Elementwise multiplication of transformed_time_series and transformed_query_segment to get transformed_dot_product
    ComplexArray transformed_dot_product = elementwise_multiply(transformed_time_series, transformed_query_segment);

    printf("\nStep 6a:  Elementwise multiplication of transformed_time_series and transformed_query_segment to get transformed_dot_product\n");
    printComplexArray("transformed_dot_product", transformed_dot_product);
    
    // Step 6b:  Inverse Fourier transform of transformed_dot_product to get dot_product
    DoubleArray dot_product = inverse_fast_fourier_transform(transformed_dot_product, appended_time_series.length);

    printf("\nStep 6b:  Inverse Fourier transform of transformed_dot_product to get dot_product\n");
    printDoubleArray("dot_product", dot_product);

    // Free intermediate data structures
    free(appended_time_series.data);
    free(reversed_query_segment.data);
    free(appended_query_segment.data);
    free(transformed_time_series.data);
    free(transformed_query_segment.data);
    free(transformed_dot_product.data);
    
    // Step 7: // return dot_product
    return dot_product;
}

// The fast_fourier_transform and inverse_fast_fourier_transform will need to come from an external library (FFTW3).
