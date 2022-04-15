#include <filesystem>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "command_line_args.h"

// rank and process_count must be defined external to the
// command_ling_args functions to simulate the MPI variables
int rank = 0;
int process_count = 4;

//https://www.youtube.com/results?search_query=c%2B%2B+google+test+on+visual+studio+2019


TEST(CommandLineArgsTest, test_command_line_args) {
    
    //Test for command_line_args:

    void print_usage();
    
    // create string vector of simulated command line args
    std::vector<std::string> args;
    args.push_back("--input-file");
    args.push_back("input_file.csv");
    args.push_back("--output-file");
    args.push_back("output_file.csv");
    args.push_back("--window-size");
    args.push_back("10");
    args.push_back("--input-column");
    args.push_back("-5");
    
    // call parse_command_line_args
    CommandLineArgs parsed_args;


    
    parsed_args = parse_command_line_args(args);


    //test if input column is 0 or bigger
    EXPECT_FALSE(parsed_args.input_column >= 0);

    //test if window size is 2 or bigger
    EXPECT_TRUE(parsed_args.window_size >= 2);

    // call validate_command_line_args
    bool test = validate_command_line_args(parsed_args);
    EXPECT_FALSE(test);

    // verify returned CommandLineArgs struct for simulated command line arg values
    
}

