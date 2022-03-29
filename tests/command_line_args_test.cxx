#include <gtest/gtest.h>
#include "command_line_args.h"
#include <iostream>
#include <vector>

// rank and process_count must be defined external to the
// command_ling_args functions to simulate the MPI variables
int rank = 0;
int process_count = 4;


TEST(CommandLineArgsTest, test_command_line_args) {
    
    //Test for command_line_args:

    void print_usage();
    
    // create string vector of simulated command line args
    std::vector<std::string> args;
    args.push_back("input.csv");
    args.push_back("output.csv");
    args.push_back("10");
    args.push_back("-5");

    // call parse_command_line_args
    CommandLineArgs parsed_args;
    parsed_args = parse_command_line_args(args);

    // call validate_command_line_args
    void validate_command_line_args(const CommandLineArgs& command_line_args);

    EXPECT_TRUE(validate_command_line_args);
    // verify returned CommandLineArgs struct for simulated command line arg values
    

    // Some of the values can cause the process to exit:
    //    -h or --help for parse_command_line_args
    //
    //    invalid values passed in for validate_command_line_args
    //
    // Google Test can check for process exit using special assertions called "Death Assertions"
    // See "Death Assertions" in https://google.github.io/googletest/reference/assertions.html
    
    
    // create a string vector with --help
    // should print the usage message and exit

    // create CommandLineArgs structs with invalid values
    // should print which value(s) are invalid, print usage message, and exit
    

    //EXPECT_TRUE(true);
}


