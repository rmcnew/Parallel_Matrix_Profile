#include <gtest/gtest.h>
#include "stamp.h"

// rank and process count must be defined external to the
// stamp functions to simulate the MPI variable
int rank = 0;
int process_count = 4;

TEST(StampTest, test_stamp) {
    
    /* Test for stamp:

    void elementwise_minimum(MatrixProfile& matrix_profile, const DoubleArray& distance_profile, unsigned long index);

    void stamp(DoubleArray time_series, int window_size, MatrixProfile& matrix_profile);

    */

    // top-level unit tests for elementwise_minimum
    
    // top-level unit tests for stamp

    EXPECT_TRUE(true);
}


