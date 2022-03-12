#ifndef GROUP_010_COMMAND_LINE_ARGS_H
#define GROUP_010_COMMAND_LINE_ARGS_H

#define LEADER 0


struct CommandLineArgs {
    std::string input_file;
    std::string output_file;
    int window_size = 10;
    int input_column = 1;
};


void print_usage();

CommandLineArgs parse_command_line_args(std::vector<std::string> args);

void validate_command_line_args(const CommandLineArgs& command_line_args);

#endif // GROUP_010_COMMAND_LINE_ARGS_H

