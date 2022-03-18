#ifndef GROUP_010_FOURIER_TRANSFORM_H
#define GROUP_010_FOURIER_TRANSFORM_H

#include "types.h"

ComplexArray fast_fourier_transform(const DoubleArray& double_array);

// output_length is needed for proper size and scaling of output
DoubleArray inverse_fast_fourier_transform(const ComplexArray& complex_array, unsigned long output_length);

#endif // GROUP_010_FOURIER_TRANSFORM_H

