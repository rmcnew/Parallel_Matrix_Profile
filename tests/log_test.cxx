#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include "log.h"
#include "timing.h"

// rank must be defined external to the
// log functions to simulate the MPI variable
int rank = 0;

TEST(LogTest, test_logging) {
    
    /* Test for logging:

	std::string get_log_filename();

    void start_logging();

    void stop_logging();

    void log(const char* format, ...);

    */

    // start_logging
    start_timer();
    start_logging();

    // log some messages
    log("There once was a %s that %s", "ship", "put to sea");

    log("And the %s was the %s", "name of that ship", "Billy O'Tea");

    log("The %s her %s down", "winds blew hard", "bow dipped");

    log("Blow %s blow", "me Billy boys");

    // stop logging
    stop_logging();

    // verify log file exists
    std::string log_filename = get_log_filename();
    printf("log_filename is: %s\n", log_filename.c_str());
    std::filesystem::path log_file(log_filename);
    bool log_file_exists = std::filesystem::exists(log_file);
    printf("log_file_exists: %d\n", log_file_exists);
    EXPECT_TRUE(log_file_exists);

    // open log file and read contents
    std::ifstream infile(log_filename);
    bool infile_good = infile.good();

    printf("infile_good: %d\n", infile_good);
    EXPECT_TRUE(infile_good);

    // verify that log contents has the expected messages
    if (infile_good) {

        int line_count = 0;
        std::string line;
        double elapsed_time = 0.0;
        int process_rank = -1;
        char log_entry[128];
    
        while (std::getline(infile, line)) {
            printf("line is: %s\n", line.c_str());
            int scanned_count = sscanf(line.c_str(), "%lf [Process_%d] %[ 'A-Za-z]", &elapsed_time, &process_rank, log_entry);
            printf("scanned_count: %d\n", scanned_count);
            EXPECT_EQ(scanned_count, 3);

            printf("elapsed_time: %f\n", elapsed_time);
            EXPECT_TRUE(elapsed_time > 0.0);

            printf("process_rank: %d\n", process_rank);
            EXPECT_EQ(process_rank, 0);

            if (line_count == 0) {
                EXPECT_STREQ("There once was a ship that put to sea", log_entry); 
            } else if (line_count == 1) {
                EXPECT_STREQ("And the name of that ship was the Billy O'Tea", log_entry);
            } else if (line_count == 2) {
                EXPECT_STREQ("The winds blew hard her bow dipped down", log_entry);
            } else if (line_count == 3) {
                EXPECT_STREQ("Blow me Billy boys blow", log_entry);
            } else { // only four lines should be logged
                FAIL();
            }
            line_count++;
        }
    }

    // delete the log file
    std::filesystem::remove(log_file);
}

