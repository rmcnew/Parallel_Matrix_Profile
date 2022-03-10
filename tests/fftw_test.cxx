#include <gtest/gtest.h>
#include <fftw3.h>

TEST(FftwTest, fftw) {
    
    // the input is N real numbers, while the output is (N/2) + 1 complex numbers 
    int N = 10;
    int C = (N/2) + 1;
    double* in;
    double* result;
    fftw_complex* out;
    fftw_plan forward_fft_plan;
    fftw_plan inverse_fft_plan;

    // allocate 
    in = (double*) malloc(sizeof(double) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * C);
    result = (double*) malloc(sizeof(double) * N);

    // ALWAYS create plans before populating the input data
    forward_fft_plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    inverse_fft_plan = fftw_plan_dft_c2r_1d(C, out, result, FFTW_ESTIMATE);

    // populate input data
    for (int i = 0; i < N; i++) {
        in[0] = (double) i;
    }

    // execute the transforms
    fftw_execute(forward_fft_plan);
    fftw_execute(inverse_fft_plan);

    // compare results
    for (int j = 0; j < N; j++) {
        EXPECT_EQ(in[i], result[i]);
    }

    // clean up allocations
    fftw_destroy_plan(forward_fft_plan);
    fftw_destroy_plan(inverse_fft_plan);
    fftw_free(out);
    free(in);
    free(result);

}

