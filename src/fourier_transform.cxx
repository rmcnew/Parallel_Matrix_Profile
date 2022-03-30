#include <cstdlib>
#include <fftw3.h>

#include "fourier_transform.h"


ComplexArray fast_fourier_transform(const DoubleArray& double_array) {
    // prepare output ComplexArray
    ComplexArray complex_array;
    complex_array.length = (double_array.length / 2) + 1;
    complex_array.data = (std::complex<long double>*) calloc (complex_array.length, sizeof(std::complex<long double>));

	// higher-precision output
	long double temp_in[double_array.length];
	for (unsigned long i = 0; i < double_array.length; i++) {
		temp_in[i] = (long double) double_array.data[i];
	}

    // prepare FFTW3 output type and plan
    fftwl_complex* out = (fftwl_complex*) fftwl_malloc(complex_array.length * sizeof(fftwl_complex));
    fftwl_plan forward_fft_plan = fftwl_plan_dft_r2c_1d(double_array.length, temp_in, out, FFTW_ESTIMATE);

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

DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array, unsigned long output_length) {
    // prepare output DoubleArray
    DoubleArray double_array;
    double_array.length = output_length;
    double_array.data = (double*) calloc (double_array.length, sizeof(double));
    
	// higher-precision output
	long double temp_out[output_length];	
    // prepare FFTW input type and plan
    fftwl_complex* in = (fftwl_complex*) fftwl_malloc(complex_array.length * sizeof(fftwl_complex));
    fftwl_plan inverse_fft_plan = fftwl_plan_dft_c2r_1d(double_array.length, in, temp_out, FFTW_ESTIMATE);

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
    long double dN = (long double) double_array.length;
    for (unsigned long i = 0; i < double_array.length; i++) {
        double_array.data[i] = (double) (temp_out[i] / dN);
    }

    return double_array;
}
