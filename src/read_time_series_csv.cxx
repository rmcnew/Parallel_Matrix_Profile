
#include "csv.hpp"
#include "read_time_series_csv.h"




DoubleArray read_time_series_csv_file(std::string input_file, int input_column) {
    DoubleArray time_series;

    // csv-parser has been included and is available through "csv.hpp"
    // See documentation: https://github.com/vincentlaucsb/csv-parser

    // open input_file
    // read values from the specified input_column (we assume computer's memory will hold all the values)
    // close input_file
    // set time_series.length to number of values read from the file
    // allocate a double array of sufficient length and copy read-in values into it

    return time_series;
}
