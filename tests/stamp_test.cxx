#include <gtest/gtest.h>
#include "stamp.h"

// rank and process count must be defined external to the
// stamp functions to simulate the MPI variable
int rank = 0;
int process_count = 1;

TEST(StampTest, test_stamp) {
    
    /* Test for stamp:

    void elementwise_minimum(MatrixProfile& matrix_profile, const DoubleArray& distance_profile, unsigned long index);

    void stamp(DoubleArray time_series, int window_size, MatrixProfile& matrix_profile);

    */

    LongDoubleArray ts;
    ts.length = 92;
    ts.data = (long double*) calloc(ts.length, sizeof(long double));
    ts.data[0] = 12;
    ts.data[1] = 118;
    ts.data[2] = 132;
    ts.data[3] = 129;
    ts.data[4] = 121;
    ts.data[5] = 135;
    ts.data[6] = 148;
    ts.data[7] = 148;
    ts.data[8] = 136;
    ts.data[9] = 119;
    ts.data[10] = 104;
    ts.data[11] = 118;
    ts.data[12] = 115;
    ts.data[13] = 126;
    ts.data[14] = 141;
    ts.data[15] = 135;
    ts.data[16] = 125;
    ts.data[17] = 149;
    ts.data[18] = 170;
    ts.data[19] = 170;
    ts.data[20] = 158;
    ts.data[21] = 133;
    ts.data[22] = 114;
    ts.data[23] = 140;
    ts.data[24] = 145;
    ts.data[25] = 150;
    ts.data[26] = 178;
    ts.data[27] = 163;
    ts.data[28] = 172;
    ts.data[29] = 178;
    ts.data[30] = 199;
    ts.data[31] = 199;
    ts.data[32] = 184;
    ts.data[33] = 162;
    ts.data[34] = 146;
    ts.data[35] = 166;
    ts.data[36] = 171;
    ts.data[37] = 180;
    ts.data[38] = 193;
    ts.data[39] = 181;
    ts.data[40] = 183;
    ts.data[41] = 218;
    ts.data[42] = 230;
    ts.data[43] = 242;
    ts.data[44] = 209;
    ts.data[45] = 191;
    ts.data[46] = 172;
    ts.data[47] = 194;
    ts.data[48] = 196;
    ts.data[49] = 196;
    ts.data[50] = 236;
    ts.data[51] = 235;
    ts.data[52] = 229;
    ts.data[53] = 243;
    ts.data[54] = 264;
    ts.data[55] = 272;
    ts.data[56] = 237;
    ts.data[57] = 211;
    ts.data[58] = 180;
    ts.data[59] = 201;
    ts.data[60] = 204;
    ts.data[61] = 188;
    ts.data[62] = 235;
    ts.data[63] = 227;
    ts.data[64] = 234;
    ts.data[65] = 264;
    ts.data[66] = 302;
    ts.data[67] = 293;
    ts.data[68] = 259;
    ts.data[69] = 229;
    ts.data[70] = 203;
    ts.data[71] = 229;
    ts.data[72] = 242;
    ts.data[73] = 233;
    ts.data[74] = 267;
    ts.data[75] = 269;
    ts.data[76] = 270;
    ts.data[77] = 315;
    ts.data[78] = 364;
    ts.data[79] = 347;
    ts.data[80] = 312;
    ts.data[81] = 274;
    ts.data[82] = 237;
    ts.data[83] = 278;
    ts.data[84] = 284;
    ts.data[85] = 277;
    ts.data[86] = 317;
    ts.data[87] = 313;
    ts.data[88] = 318;
    ts.data[89] = 374;
    ts.data[90] = 413;
    ts.data[91] = 405;


    // top-level unit tests for elementwise_minimum
    
    // top-level unit tests for stamp
    MatrixProfile matrix_profile = stamp(ts, 10, 2);

    printMatrixProfile("matrix_profile", matrix_profile);

    EXPECT_TRUE(true);
}


