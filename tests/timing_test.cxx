#include <gtest/gtest.h>
#include "timing.h"

TEST(TimingTest, test_timing) {
    
    /* Tests for Timing:
     
    void start_timer();

    void stop_timer();

    double get_elapsed_time();

    double get_overall_elapsed_time();

    */
    
    // start timer
    // wait a bit
    // get elapsed time (should be greater than 0)
    // wait a bit more
    // get elapsed time (should be greater than previous elapsed time)
    // stop timer
    // get overall elapsed time (should be greater than previous elapsed time)

    EXPECT_TRUE(true);
}

