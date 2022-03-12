#include <fftw3.h>

#include "fourier_transform.h"


ComplexArray fast_fourier_transform(const DoubleArray& double_array) {
    ComplexArray complex_array;

    // compute the Fourier transform using FFTW3; see tests/fftw_test.cxx

    return complex_array;
}

DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array) {
    DoubleArray double_array;
    
    // compute the inverse Fourier transform using FFTW3; see tests/fftw_test.cxx
    // NOTE that the result will need to be normalized!

    return double_array;
}
