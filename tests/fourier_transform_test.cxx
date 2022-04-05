#include <complex>
#include <cstdlib>
#include <gtest/gtest.h>
#include "fourier_transform.h"


TEST(FourierTransformTest, test_fourier_transform) {
    
    /* Test for fourier_transform:

    ComplexArray fast_fourier_transform(const DoubleArray& double_array);

    DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array, unsigned long output_length);

    */

    // create a DoubleArray of test data
    LongDoubleArray d1;
    d1.length = 9;
    d1.data = (long double*) calloc(d1.length, sizeof(long double));
    d1.data[0] = 11.0L;
    d1.data[1] = 22.0L;
    d1.data[2] = 33.0L;
    d1.data[3] = 44.0L;
    d1.data[4] = 55.0L;
    d1.data[5] = 66.0L;
    d1.data[6] = 77.0L;
    d1.data[7] = 88.0L;
    d1.data[8] = 99.0L;

    // pre-computed result
    ComplexArray expected_d1_fft;
    expected_d1_fft.length = 5;
    expected_d1_fft.data = (std::complex<long double>*) calloc(expected_d1_fft.length, sizeof(std::complex<long double>));
    expected_d1_fft.data[0].real(495.0);
    expected_d1_fft.data[0].imag(0.0);
    expected_d1_fft.data[1].real(-49.5);
    expected_d1_fft.data[1].imag(136.00013226300379);
    expected_d1_fft.data[2].real(-49.5);
    expected_d1_fft.data[2].imag(58.991802833413388);
    expected_d1_fft.data[3].real(-49.5);
    expected_d1_fft.data[3].imag(28.578838324886473);
    expected_d1_fft.data[4].real(-49.5);
    expected_d1_fft.data[4].imag(8.7281855450690156);

    // run test data through fast_fourier_transform
    ComplexArray d1_fft = fast_fourier_transform(d1);

    // verify ComplexArray result against a pre-computed result
    EXPECT_EQ(expected_d1_fft.length, d1_fft.length);
    for (unsigned long j = 0; j < expected_d1_fft.length; j++) {
        EXPECT_DOUBLE_EQ(expected_d1_fft.data[j].real(), d1_fft.data[j].real());
        EXPECT_DOUBLE_EQ(expected_d1_fft.data[j].imag(), d1_fft.data[j].imag());
    }

    // run the ComplexArray result through inverse_fast_fourier_transform
    LongDoubleArray d2 = inverse_fast_fourier_transform(d1_fft, d1.length);

    // verify the result matches the original test data
    EXPECT_EQ(d1.length, d2.length);
    for (unsigned long i = 0; i < d1.length; i++) {
        EXPECT_DOUBLE_EQ((double)d1.data[i], (double)d2.data[i]);
    }

    // free allocated memory
    free(d1.data);
    free(expected_d1_fft.data);
    free(d1_fft.data);
    free(d2.data);
}

