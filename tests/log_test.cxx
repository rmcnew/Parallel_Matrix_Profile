#include <gtest/gtest.h>
#include "log.h"

// rank must be defined external to the
// log functions to simulate the MPI variable
int rank = 0;

TEST(LogTest, test_logging) {
    
    /* Test for logging:

    void start_logging();

    void stop_logging();

    void log(const char* format, ...);

    */

    // start_logging
    // log some messages
    // stop logging
    // check for existence of log file
    // open log file and read contents
    // verify that log contents has the expected messages
    

    EXPECT_TRUE(true);
}

