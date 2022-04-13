#include <cstdlib>
#include <vector>
#include "csv.hpp"
#include "read_time_series_csv.h"

LongDoubleArray read_time_series_csv_file(std::string input_file, int input_column) {

    LongDoubleArray time_series;

    size_t column = (size_t) input_column;
    
    // csv-parser has been included and is available through "csv.hpp"
    // See documentation: https://github.com/vincentlaucsb/csv-parser
    
    // open input_file
    csv::CSVReader reader(input_file);
    
    std::vector<long double> values;

    // read values from the specified input_column (we assume computer's memory will hold all the values)
    for (const csv::CSVRow& row : reader) {
        long double value = row[column].get<long double>();
        values.push_back(value);
    }

    // set time_series.length to number of values read from the file
    time_series.length = (unsigned long) values.size();

    // allocate a double array of sufficient length and copy read-in values into it
    time_series.data = (long double*) calloc(time_series.length, sizeof(long double));
    
    for (unsigned long i = 0; i < time_series.length; i++) {
        time_series.data[i] = values[i];
    }

    // close input_file handled by CSVReader destructor

    return time_series;
}
