#ifndef GROUP_010_FOURIER_TRANSFORM_H
#define GROUP_010_FOURIER_TRANSFORM_H

#include "types.h"

ComplexArray fast_fourier_transform(const DoubleArray& double_array);

DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array);

#endif // GROUP_010_FOURIER_TRANSFORM_H

