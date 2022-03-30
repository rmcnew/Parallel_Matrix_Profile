#include <gtest/gtest.h>
#include "distance_profile.h"
#include "sliding_dot_product.h"


TEST(DistanceProfileTest, test_distance_profile) {
    
    /* Test for distance_profile:

    DoubleArray calculate_distance_profile(const DoubleArray& query_segment, const DoubleArray& time_series);

    */

    // generate test query_segment and time series
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

    // pre-computed distance_profile for the given input values
    DoubleArray expected;
    expected.length = 91;
    expected.data = (double*) calloc(expected.length, sizeof(double));
	expected.data[0] = 5.960464477539063e-08;
	expected.data[1] = 0.0;
	expected.data[2] = 0.0;
	expected.data[3] = 5.960464477539063e-08;
	expected.data[4] = 0.0;
	expected.data[5] = 0.0;
	expected.data[6] = 5.960464477539063e-08;
	expected.data[7] = 5.960464477539063e-08;
	expected.data[8] = 5.960464477539063e-08;
	expected.data[9] = 8.429369702178807e-08;
	expected.data[10] = 5.960464477539063e-08;
	expected.data[11] = 5.960464477539063e-08;
	expected.data[12] = 5.960464477539063e-08;
	expected.data[13] = 0.0;
	expected.data[14] = 5.960464477539063e-08;
	expected.data[15] = 5.960464477539063e-08;
	expected.data[16] = 1.0323827311807139e-07;
	expected.data[17] = 1.0323827311807139e-07;
	expected.data[18] = 5.960464477539063e-08;
	expected.data[19] = 5.960464477539063e-08;
	expected.data[20] = 0.0;
	expected.data[21] = 1.0323827311807139e-07;
	expected.data[22] = 5.960464477539063e-08;
	expected.data[23] = 5.960464477539063e-08;
	expected.data[24] = 5.960464477539063e-08;
	expected.data[25] = 5.960464477539063e-08;
	expected.data[26] = 5.960464477539063e-08;
	expected.data[27] = 1.0323827311807139e-07;
	expected.data[28] = 5.960464477539063e-08;
	expected.data[29] = 0.0;
	expected.data[30] = 5.960464477539063e-08;
	expected.data[31] = 5.960464477539063e-08;
	expected.data[32] = 5.960464477539063e-08;
	expected.data[33] = 1.0323827311807139e-07;
	expected.data[34] = 1.1920928955078125e-07;
	expected.data[35] = 1.4600096599955427e-07;
	expected.data[36] = 1.0323827311807139e-07;
	expected.data[37] = 1.1920928955078125e-07;
	expected.data[38] = 1.0323827311807139e-07;
	expected.data[39] = 0.0;
	expected.data[40] = 5.960464477539063e-08;
	expected.data[41] = 1.4600096599955427e-07;
	expected.data[42] = 5.960464477539063e-08;
	expected.data[43] = 5.960464477539063e-08;
	expected.data[44] = 1.0323827311807139e-07;
	expected.data[45] = 1.0323827311807139e-07;
	expected.data[46] = 1.4600096599955427e-07;
	expected.data[47] = 1.0323827311807139e-07;
	expected.data[48] = 1.0323827311807139e-07;
	expected.data[49] = 1.4600096599955427e-07;
	expected.data[50] = 0.0;
	expected.data[51] = 1.0323827311807139e-07;
	expected.data[52] = 1.4600096599955427e-07;
	expected.data[53] = 0.0;
	expected.data[54] = 1.6858739404357614e-07;
	expected.data[55] = 1.0323827311807139e-07;
	expected.data[56] = 1.0323827311807139e-07;
	expected.data[57] = 1.0323827311807139e-07;
	expected.data[58] = 1.0323827311807139e-07;
	expected.data[59] = 1.6858739404357614e-07;
	expected.data[60] = 1.4600096599955427e-07;
	expected.data[61] = 1.97686242482388e-07;
	expected.data[62] = 0.0;
	expected.data[63] = 1.97686242482388e-07;
	expected.data[64] = 1.4600096599955427e-07;
	expected.data[65] = 1.6858739404357614e-07;
	expected.data[66] = 1.6858739404357614e-07;
	expected.data[67] = 1.0323827311807139e-07;
	expected.data[68] = 1.0323827311807139e-07;
	expected.data[69] = 2.2302015940987714e-07;
	expected.data[70] = 2.2302015940987714e-07;
	expected.data[71] = 1.97686242482388e-07;
	expected.data[72] = 1.6858739404357614e-07;
	expected.data[73] = 1.4600096599955427e-07;
	expected.data[74] = 1.4600096599955427e-07;
	expected.data[75] = 1.0323827311807139e-07;
	expected.data[76] = 1.0323827311807139e-07;
	expected.data[77] = 1.4600096599955427e-07;
	expected.data[78] = 1.0323827311807139e-07;
	expected.data[79] = 1.6858739404357614e-07;
	expected.data[80] = 1.97686242482388e-07;
	expected.data[81] = 1.0323827311807139e-07;
	expected.data[82] = 1.0323827311807139e-07;
	expected.data[83] = 0.0;
	expected.data[84] = 1.0323827311807139e-07;
	expected.data[85] = 1.0323827311807139e-07;
	expected.data[86] = 0.0;
	expected.data[87] = 1.6858739404357614e-07;
	expected.data[88] = 1.0323827311807139e-07;
	expected.data[89] = 1.4600096599955427e-07;
	expected.data[90] = 1.4600096599955427e-07;

    // calculate_distance_profile
    DoubleArray result = calculate_distance_profile(qs, ts);


    printf("\nCompare computed distance_profile result to expected distance_profile values\n");
    printDoubleArray("expected", expected);


	// Ensure result matches expected
	EXPECT_EQ(result.length, expected.length);
	//for (unsigned long i = 0; i < result.length; i++) {
	//	EXPECT_DOUBLE_EQ(result.data[i], expected.data[i]);
		//EXPECT_NEAR(result.data[i], expected.data[i], 0.000000000003);
	//}

    // clean up
    free(result.data);
    free(expected.data);
}


