
#include "csv.hpp"
#include "read_time_series_csv.h"
#include <list>
using namespace csv;



DoubleArray read_time_series_csv_file(std::string input_file, int input_column) {
    DoubleArray time_series;
    CSVReader reader(input_file);
    std::list<std::list <float>> data;
    
    for (CSVRow& row : reader) {
        std::list<std::float> row_data;
        for (CSVField& field : row) {
            row_data.push_back(field.get<>());
        }
        data.push_back(row_data);
    }
    // csv-parser has been included and is available through "csv.hpp"
    // See documentation: https://github.com/vincentlaucsb/csv-parser

    // open input_file
    // read values from the specified input_column (we assume computer's memory will hold all the values)
    // close input_file
    // set time_series.length to number of values read from the file
    // allocate a double array of sufficient length and copy read-in values into it

    return time_series;
}
