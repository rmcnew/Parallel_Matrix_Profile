#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <fftw3.h>

TEST(FftwTest, fftw) {
    
    // the input is N real numbers, while the output is (N/2) + 1 complex numbers 
    int N = 10;
    int C = (N/2) + 1;
    long double* in;
    long double* result;
    fftwl_complex* out;
    fftwl_plan forward_fft_plan;
    fftwl_plan inverse_fft_plan;

    // allocate 
    in = (long double*) calloc(N, sizeof(long double));
    out = (fftwl_complex*) fftwl_malloc(sizeof(fftwl_complex) * N);
    result = (long double*) calloc(N, sizeof(long double));

    // ALWAYS create plans before populating the input data
    forward_fft_plan = fftwl_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    inverse_fft_plan = fftwl_plan_dft_c2r_1d(N, out, result, FFTW_ESTIMATE);

    // populate input data
    for (int i = 0; i < N; i++) {
        in[i] = (long double) i;
    }

    // execute the transforms
    //printf("Before FFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%Lf,%Lf), result: %Lf\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}
    fftwl_execute(forward_fft_plan);
    //printf("After FFT, Before IFFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%Lf,%Lf), result: %Lf\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}
    fftwl_execute(inverse_fft_plan);
    //printf("After IFFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%Lf,%Lf), result: %Lf\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}

    // FFTW3 documentation states:
    // "FFTW computes an unnormalized DFT. Thus, computing a forward followed by a backward transform (or vice versa) results in the original array scaled by n."
    long double dN = (long double) N;
    // normalize result
    for (int i = 0; i < N; i++) {
        if (result[i] != 0.0) {
            result[i] = result[i] / dN;
        }
    }


    // compare results
    for (int i = 0; i < N; i++) {
        EXPECT_DOUBLE_EQ(in[i], result[i]);
    }

    // clean up allocations
    fftwl_destroy_plan(forward_fft_plan);
    fftwl_destroy_plan(inverse_fft_plan);
    fftwl_free(out);
    free(in);
    free(result);

}

