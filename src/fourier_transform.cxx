#include <cstdlib>
#include <fftw3.h>

#include "fourier_transform.h"


ComplexArray fast_fourier_transform(const LongDoubleArray& input) {
    // prepare output ComplexArray
    ComplexArray complex_array;
    complex_array.length = (input.length / 2) + 1;
    complex_array.data = (std::complex<long double>*) calloc (complex_array.length, sizeof(std::complex<long double>));

    // prepare FFTW3 output type and plan
    fftwl_complex* out = (fftwl_complex*) fftwl_malloc(complex_array.length * sizeof(fftwl_complex));
    fftwl_plan forward_fft_plan = fftwl_plan_dft_r2c_1d(input.length, input.data, out, FFTW_ESTIMATE);

    // execute FFT
    fftwl_execute(forward_fft_plan);

    // copy results into output ComplexArray
    for (unsigned long i = 0; i < complex_array.length; i++) {
        complex_array.data[i].real(out[i][0]);
        complex_array.data[i].imag(out[i][1]);
    }
    
    // free FFTW3 output type and plan
    fftwl_destroy_plan(forward_fft_plan);
    fftwl_free(out);

    return complex_array;
}

LongDoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array, unsigned long output_length) {
    // prepare output 
    LongDoubleArray output;
    output.length = output_length;
    output.data = (long double*) calloc (output.length, sizeof(long double));
    
    // prepare FFTW input type and plan
    fftwl_complex* in = (fftwl_complex*) fftwl_malloc(complex_array.length * sizeof(fftwl_complex));
    fftwl_plan inverse_fft_plan = fftwl_plan_dft_c2r_1d(output.length, in, output.data, FFTW_ESTIMATE);

    // copy input ComplexArray into fftw input type
    for (unsigned long i = 0; i < complex_array.length; i++) {
        in[i][0] = complex_array.data[i].real();
        in[i][1] = complex_array.data[i].imag();
    }

    // execute inverse FFT
    fftwl_execute(inverse_fft_plan);

    // free FFTW3 input type and plan
    fftwl_destroy_plan(inverse_fft_plan);
    fftwl_free(in);

    // normalize result
    long double dN = (long double) output.length;
    for (unsigned long i = 0; i < output.length; i++) {
        output.data[i] = (output.data[i] / dN);
    }

    return output;
}
