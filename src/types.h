#ifndef GROUP_010_TYPES_H
#define GROUP_010_TYPES_H

#include <complex>

struct DoubleArray {
    double* data = nullptr;
    unsigned long length = 0;
};

struct LongDoubleArray {
    long double* data = nullptr;
    unsigned long length = 0;
};


struct MatrixProfile {
    long double* data = nullptr;
    unsigned long length = 0;
    unsigned long* index = nullptr;
};


struct ComplexArray {
    std::complex<long double>* data = nullptr;
    unsigned long length = 0;
};

#endif // GROUP_010_TYPES_H

