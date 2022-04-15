#ifndef GROUP_010_STAMP_H
#define GROUP_010_STAMP_H

#include "types.h"


void printMatrixProfile(const std::string& name, const MatrixProfile& matrix_profile);

void logMatrixProfile(const std::string& name, const MatrixProfile& mp);

MatrixProfile stamp(const LongDoubleArray& time_series, const int& window_size, const unsigned long& exclusion_radius);

#endif // GROUP_010_STAMP_H

