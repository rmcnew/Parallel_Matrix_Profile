#ifndef GROUP_010_STAMP_H
#define GROUP_010_STAMP_H

#include "types.h"

void elementwise_minimum(MatrixProfile& matrix_profile, const DoubleArray& distance_profile, unsigned long index);

void stamp(DoubleArray time_series, int window_size, MatrixProfile& matrix_profile);

#endif // GROUP_010_STAMP_H

