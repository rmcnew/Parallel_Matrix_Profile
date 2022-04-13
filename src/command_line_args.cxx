#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "command_line_args.h"

extern int rank;
extern int process_count;

// ***** Command Line Arguments *****

void leader_print(const char* str) {
    if (rank == LEADER) {
        printf("%s\n", str);
    }
}

// Print usage help
void print_usage() {
    leader_print("\n\nUsage: mpirun -n <PROCESS_COUNT> -f <hostfile> ./matrix_profile --input-file <INPUT_FILE.CSV> --output-file <OUTPUT_FILE.CSV> [--window-size WINDOW_SIZE] [--input-column INPUT_COLUMN]");
}


CommandLineArgs parse_command_line_args(std::vector<std::string> args) {

    CommandLineArgs command_line_args;

    for (auto arg = args.begin(); arg != args.end(); arg++) {
        if (*arg == "-h" || *arg == "--help") {
            command_line_args.help_wanted = true;
        }
        else if (*arg == "--input-file") {
            arg++;
            command_line_args.input_file = *arg;
        }
        else if (*arg == "--output-file") {
            arg++;
            command_line_args.output_file = *arg;
        }
        else if (*arg == "--window-size") {
            arg++;
            std::string window_size_str = *arg; //0-inf
            command_line_args.window_size = std::stoi(window_size_str);
        }
        else if (*arg == "--input-column") {
            arg++;
            std::string input_column_str = *arg; //0-inf
            command_line_args.input_column = std::stoi(input_column_str);
        }
    }
    
    return command_line_args;
}
//https://en.cppreference.com/w/cpp/filesystem 

bool validate_command_line_args(const CommandLineArgs& command_line_args) {
    bool valid = true; // set to false if failed any of the checks

    // check that input_file exists and can be read
    namespace fs = std::filesystem;
    fs::path f{ command_line_args.input_file };

    if (!fs::exists(f)) { 
        leader_print("input_file not found!  Check path and filename.");
        valid = false;
    }

    // if present, window_size must be 2 or greater
    if (command_line_args.window_size <= 1) {
        valid = false;
        leader_print("window_size must be 2 or greater!");
    }

    // if present, input_column must be 0 or positive
    if (command_line_args.input_column < 0) {
        valid = false;
        leader_print("input_column must be greater than 0!");
    }

    if (valid && rank == LEADER) {
        printf("Running with %d processes\nUsing input_file: %s and output_file: %s\nUsing window_size: %d and input_column: %d\n", process_count, command_line_args.input_file.c_str(), command_line_args.output_file.c_str(), command_line_args.window_size, command_line_args.input_column);
    }

    return valid;
}
