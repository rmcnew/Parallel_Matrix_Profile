#include <cstdio>
#include <gtest/gtest.h>
#include "sliding_dot_product.h"


TEST(SlidingDotProductTest, test_sliding_dot_product) {
    
    /* Test for sliding_dot_product:

    ComplexArray elementwise_multiply(const ComplexArray& transformed_query_segment, const ComplexArray& transformed_time_series);

    DoubleArray sliding_dot_product(const DoubleArray& query_segment, const DoubleArray& time_series);

    */

    DoubleArray ts;
    ts.length = 100;
    ts.data = (double*) calloc(ts.length, sizeof(double));
    ts.data[0] = 1.0;
    ts.data[1] = 2.0;
    ts.data[2] = 3.0;
    ts.data[3] = 4.0;
    ts.data[4] = 5.0;
    ts.data[5] = 6.0;
    ts.data[6] = 7.0;
    ts.data[7] = 8.0;
    ts.data[8] = 9.0;
    ts.data[9] = 10.0;
    ts.data[10] = 11.0;
    ts.data[11] = 12.0;
    ts.data[12] = 13.0;
    ts.data[13] = 14.0;
    ts.data[14] = 15.0;
    ts.data[15] = 16.0;
    ts.data[16] = 17.0;
    ts.data[17] = 18.0;
    ts.data[18] = 19.0;
    ts.data[19] = 20.0;
    ts.data[20] = 21.0;
    ts.data[21] = 22.0;
    ts.data[22] = 23.0;
    ts.data[23] = 24.0;
    ts.data[24] = 25.0;
    ts.data[25] = 26.0;
    ts.data[26] = 27.0;
    ts.data[27] = 28.0;
    ts.data[28] = 29.0;
    ts.data[29] = 30.0;
    ts.data[30] = 31.0;
    ts.data[31] = 32.0;
    ts.data[32] = 33.0;
    ts.data[33] = 34.0;
    ts.data[34] = 35.0;
    ts.data[35] = 36.0;
    ts.data[36] = 37.0;
    ts.data[37] = 38.0;
    ts.data[38] = 39.0;
    ts.data[39] = 40.0;
    ts.data[40] = 41.0;
    ts.data[41] = 42.0;
    ts.data[42] = 43.0;
    ts.data[43] = 44.0;
    ts.data[44] = 45.0;
    ts.data[45] = 46.0;
    ts.data[46] = 47.0;
    ts.data[47] = 48.0;
    ts.data[48] = 49.0;
    ts.data[49] = 50.0;
    ts.data[50] = 51.0;
    ts.data[51] = 52.0;
    ts.data[52] = 53.0;
    ts.data[53] = 54.0;
    ts.data[54] = 55.0;
    ts.data[55] = 56.0;
    ts.data[56] = 57.0;
    ts.data[57] = 58.0;
    ts.data[58] = 59.0;
    ts.data[59] = 60.0;
    ts.data[60] = 61.0;
    ts.data[61] = 62.0;
    ts.data[62] = 63.0;
    ts.data[63] = 64.0;
    ts.data[64] = 65.0;
    ts.data[65] = 66.0;
    ts.data[66] = 67.0;
    ts.data[67] = 68.0;
    ts.data[68] = 69.0;
    ts.data[69] = 70.0;
    ts.data[70] = 71.0;
    ts.data[71] = 72.0;
    ts.data[72] = 73.0;
    ts.data[73] = 74.0;
    ts.data[74] = 75.0;
    ts.data[75] = 76.0;
    ts.data[76] = 77.0;
    ts.data[77] = 78.0;
    ts.data[78] = 79.0;
    ts.data[79] = 80.0;
    ts.data[80] = 81.0;
    ts.data[81] = 82.0;
    ts.data[82] = 83.0;
    ts.data[83] = 84.0;
    ts.data[84] = 85.0;
    ts.data[85] = 86.0;
    ts.data[86] = 87.0;
    ts.data[87] = 88.0;
    ts.data[88] = 89.0;
    ts.data[89] = 90.0;
    ts.data[90] = 91.0;
    ts.data[91] = 92.0;
    ts.data[92] = 93.0;
    ts.data[93] = 94.0;
    ts.data[94] = 95.0;
    ts.data[95] = 96.0;
    ts.data[96] = 97.0;
    ts.data[97] = 98.0;
    ts.data[98] = 99.0;
    ts.data[99] = 100.0;
    
    DoubleArray qs;
    qs.length = 10;
    qs.data = &(ts.data[5]);

    DoubleArray result = sliding_dot_product(qs, ts);

    DoubleArray expected;
	expected.length = 91;
	expected.data = (double*) calloc(expected.length, sizeof(double));
	expected.data[0] = 660.0;
	expected.data[1] = 765.0;
	expected.data[2] = 870.0;
	expected.data[3] = 975.0;
	expected.data[4] = 1080.0;
	expected.data[5] = 1185.0;
	expected.data[6] = 1290.0;
	expected.data[7] = 1395.0;
	expected.data[8] = 1500.0;
	expected.data[9] = 1605.0;
	expected.data[10] = 1710.0;
	expected.data[11] = 1815.0;
	expected.data[12] = 1920.0;
	expected.data[13] = 2025.0;
	expected.data[14] = 2130.0;
	expected.data[15] = 2235.0;
	expected.data[16] = 2340.0;
	expected.data[17] = 2445.0;
	expected.data[18] = 2550.0;
	expected.data[19] = 2655.0;
	expected.data[20] = 2760.0;
	expected.data[21] = 2865.0;
	expected.data[22] = 2970.0;
	expected.data[23] = 3075.0;
	expected.data[24] = 3180.0;
	expected.data[25] = 3285.0;
	expected.data[26] = 3390.0;
	expected.data[27] = 3495.0;
	expected.data[28] = 3600.0;
	expected.data[29] = 3705.0;
	expected.data[30] = 3810.0;
	expected.data[31] = 3915.0;
	expected.data[32] = 4020.0;
	expected.data[33] = 4125.0;
	expected.data[34] = 4230.0;
	expected.data[35] = 4335.0;
	expected.data[36] = 4440.0;
	expected.data[37] = 4545.0;
	expected.data[38] = 4650.0;
	expected.data[39] = 4755.0;
	expected.data[40] = 4860.0;
	expected.data[41] = 4965.0;
	expected.data[42] = 5070.0;
	expected.data[43] = 5175.0;
	expected.data[44] = 5280.0;
	expected.data[45] = 5385.0;
	expected.data[46] = 5490.0;
	expected.data[47] = 5595.0;
	expected.data[48] = 5700.0;
	expected.data[49] = 5805.0;
	expected.data[50] = 5910.0;
	expected.data[51] = 6015.0;
	expected.data[52] = 6120.0;
	expected.data[53] = 6225.0;
	expected.data[54] = 6330.0;
	expected.data[55] = 6435.0;
	expected.data[56] = 6540.0;
	expected.data[57] = 6645.0;
	expected.data[58] = 6750.0;
	expected.data[59] = 6855.0;
	expected.data[60] = 6960.0;
	expected.data[61] = 7065.0;
	expected.data[62] = 7170.0;
	expected.data[63] = 7275.0;
	expected.data[64] = 7380.0;
	expected.data[65] = 7485.0;
	expected.data[66] = 7590.0;
	expected.data[67] = 7695.0;
	expected.data[68] = 7800.0;
	expected.data[69] = 7905.0;
	expected.data[70] = 8010.0;
	expected.data[71] = 8115.0;
	expected.data[72] = 8220.0;
	expected.data[73] = 8325.0;
	expected.data[74] = 8430.0;
	expected.data[75] = 8535.0;
	expected.data[76] = 8640.0;
	expected.data[77] = 8745.0;
	expected.data[78] = 8850.0;
	expected.data[79] = 8955.0;
	expected.data[80] = 9060.0;
	expected.data[81] = 9165.0;
	expected.data[82] = 9270.0;
	expected.data[83] = 9375.0;
	expected.data[84] = 9480.0;
	expected.data[85] = 9585.0;
	expected.data[86] = 9690.0;
	expected.data[87] = 9795.0;
	expected.data[88] = 9900.0;
	expected.data[89] = 10005.0;
	expected.data[90] = 10110.0;


    printf("\n");
    printDoubleArray("expected_sliding_dot_product", expected);

	// Ensure result matches expected
	EXPECT_EQ(result.length, expected.length);
	for (unsigned long i = 0; i < result.length; i++) {
		//EXPECT_DOUBLE_EQ(result.data[i], expected.data[i]);
		EXPECT_NEAR(result.data[i], expected.data[i], 0.000000000003);
	}

    // clean up
    free(result.data);
    free(expected.data);
}


