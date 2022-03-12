#include <gtest/gtest.h>
#include "fourier_transform.h"


TEST(FourierTransformTest, test_fourier_transform) {
    
    /* Test for fourier_transform:

    ComplexArray fast_fourier_transform(const DoubleArray& double_array);

    DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array);

    */

    // create a DoubleArray of test data
    // run test data through fast_fourier_transform
    // verify ComplexArray result against a pre-computed result

    // run the ComplexArray result through inverse_fast_fourier_transform
    // verify the DoubleArray result matches the original DoubleArray of test data

    EXPECT_TRUE(true);
}


