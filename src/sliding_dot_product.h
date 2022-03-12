#ifndef GROUP_010_SLIDING_DOT_PRODUCT_H
#define GROUP_010_SLIDING_DOT_PRODUCT_H

#include "types.h"

ComplexArray elementwise_multiply(const ComplexArray& transformed_query_segment, const ComplexArray& transformed_time_series);

DoubleArray sliding_dot_product(const DoubleArray& query_segment, const DoubleArray& time_series);

#endif // GROUP_010_SLIDING_DOT_PRODUCT_H

