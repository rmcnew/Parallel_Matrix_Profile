
#include <iostream>
#include <fstream>
#include <limits>
#include "write_matrix_profile_csv.h"


void write_matrix_profile_csv(const std::string& output_file, const MatrixProfile& matrix_profile) {

    // open output_file
    std::ofstream ostream(output_file);
    if (ostream.good()) {
        ostream.setf(std::ios::scientific);
        ostream.precision(std::numeric_limits<long double>::digits10);
        for (unsigned long i = 0; i < matrix_profile.length; i++) {
            // write matrix_profile data to output_file
            ostream << matrix_profile.data[i] << ", " << matrix_profile.index[i] << std::endl;
        }
        // flush output_file handle
        ostream.flush();
        // close output_file handle
        ostream.close();
    } else {
        std::cerr << "Could not open output file:  " << output_file << " for writing!" << std::endl;
    }
}
