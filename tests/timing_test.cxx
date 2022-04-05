#include <chrono>
#include <thread>
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
    start_timer();

    // wait a bit
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // get elapsed time (should be greater than 0)
    double e1 = get_elapsed_time();
    EXPECT_TRUE(e1 > 0.0);

    // wait a bit more
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // get elapsed time (should be greater than previous elapsed time)
    double e2 = get_elapsed_time();
    EXPECT_TRUE(e2 > 0.0);
    EXPECT_TRUE(e2 > e1);
    
    // wait a bit more
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // stop timer
    stop_timer();
    
    // get overall elapsed time (should be greater than previous elapsed time)
    double e3 = get_overall_elapsed_time();
    EXPECT_TRUE(e3 > 0.0);
    EXPECT_TRUE(e3 > e1);
    EXPECT_TRUE(e3 > e2);

}

