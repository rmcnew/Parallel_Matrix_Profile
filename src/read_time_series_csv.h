#ifndef GROUP_010_READ_TIME_SERIES_CSV_H
#define GROUP_010_READ_TIME_SERIES_CSV_H

#include <string>

struct TimeSeries {
    double* data = nullptr;
    long length = 0;
};

TimeSeries read_time_series_csv_file(std::string input_file, int input_column);



#endif // GROUP_010_READ_TIME_SERIES_CSV_H

