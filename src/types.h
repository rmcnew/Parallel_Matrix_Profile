#ifndef GROUP_010_TYPES_H
#define GROUP_010_TYPES_H

#include <complex>

struct DoubleArray {
    double* data = nullptr;
    unsigned long length = 0;
};


struct MatrixProfile {
    double* data = nullptr;
    unsigned long length = 0;
    unsigned long* index = nullptr;
};


struct ComplexArray {
    std::complex<double>* data = nullptr;
    unsigned long length = 0;
};

#endif // GROUP_010_TYPES_H

