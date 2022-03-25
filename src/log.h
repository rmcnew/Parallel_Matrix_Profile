#ifndef GROUP_010_LOG_H
#define GROUP_010_LOG_H

#include <string>

std::string get_log_filename();

void start_logging();

void stop_logging();

void log(const char* format, ...);

#endif // GROUP_010_LOG_H
