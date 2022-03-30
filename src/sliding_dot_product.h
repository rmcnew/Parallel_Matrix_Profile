#ifndef GROUP_010_SLIDING_DOT_PRODUCT_H
#define GROUP_010_SLIDING_DOT_PRODUCT_H

#include <string>
#include "types.h"

ComplexArray elementwise_multiply(const ComplexArray& transformed_query_segment, const ComplexArray& transformed_time_series);

DoubleArray sliding_dot_product(const DoubleArray& query_segment, const DoubleArray& time_series);

void printDoubleArray(const std::string& name, const DoubleArray& double_array);

void printComplexArray(const std::string& name, const ComplexArray& complex_array);

#endif // GROUP_010_SLIDING_DOT_PRODUCT_H

