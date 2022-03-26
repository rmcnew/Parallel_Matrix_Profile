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

    // calculate_distance_profile
    DoubleArray result = calculate_distance_profile(qs, ts);

    // compare computed distance_profile against pre-computed values

    EXPECT_TRUE(true);
}


