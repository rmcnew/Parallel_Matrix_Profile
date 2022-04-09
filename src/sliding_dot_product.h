#ifndef GROUP_010_SLIDING_DOT_PRODUCT_H
#define GROUP_010_SLIDING_DOT_PRODUCT_H

#include <string>
#include "types.h"

ComplexArray elementwise_multiply(const ComplexArray& transformed_query_segment, const ComplexArray& transformed_time_series);

LongDoubleArray sliding_dot_product(const LongDoubleArray& query_segment, const LongDoubleArray& time_series);

void printDoubleArray(const std::string& name, const DoubleArray& double_array);

void printLongDoubleArray(const std::string& name, const LongDoubleArray& long_double_array);

void logLongDoubleArray(const std::string& name, const LongDoubleArray& long_double_array);

void printComplexArray(const std::string& name, const ComplexArray& complex_array);

#endif // GROUP_010_SLIDING_DOT_PRODUCT_H

