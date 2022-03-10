#include <cmath>
#include <cstdio>
#include <cstdlib>
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
    in = (double*) calloc(N, sizeof(double));
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    result = (double*) calloc(N, sizeof(double));

    // ALWAYS create plans before populating the input data
    forward_fft_plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    inverse_fft_plan = fftw_plan_dft_c2r_1d(N, out, result, FFTW_ESTIMATE);

    // populate input data
    for (int i = 0; i < N; i++) {
        in[i] = (double) i;
    }

    // execute the transforms
    //printf("Before FFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%f,%f), result: %f\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}
    fftw_execute(forward_fft_plan);
    //printf("After FFT, Before IFFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%f,%f), result: %f\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}
    fftw_execute(inverse_fft_plan);
    //printf("After IFFT\n");
    //for (int i = 0; i < N; i++) {
    //    printf("%d: in: %f, out: (%f,%f), result: %f\n", i, in[i], out[i][0], out[i][1], result[i]);
    //}

    // FFTW3 documentation states:
    // "FFTW computes an unnormalized DFT. Thus, computing a forward followed by a backward transform (or vice versa) results in the original array scaled by n."
    double dN = (double) N;
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
    fftw_destroy_plan(forward_fft_plan);
    fftw_destroy_plan(inverse_fft_plan);
    fftw_free(out);
    free(in);
    free(result);

}

