#include <gtest/gtest.h>
#include "stamp.h"

// rank and process count must be defined external to the
// stamp functions to simulate the MPI variable
int rank = 0;
int process_count = 1;

TEST(StampTest, test_stamp) {
    
    /* Test for stamp:

    void printMatrixProfile(const std::string& name, const MatrixProfile& matrix_profile);

    MatrixProfile stamp(const LongDoubleArray& time_series, const int& window_size, const unsigned long& exclusion_radius);

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

	MatrixProfile expected;
	expected.length = 83;	
	expected.data = (long double*) calloc(expected.length, sizeof(long double));
	expected.data[0] = 2.3302547777034177L;
	expected.data[1] = 0.8183124686033922L;
	expected.data[2] = 0.7378075631723987L;
	expected.data[3] = 0.7074759836873623L;
	expected.data[4] = 0.8855166053784083L;
	expected.data[5] = 0.8670145349785627L;
	expected.data[6] = 0.7930125433710051L;
	expected.data[7] = 1.063508794746865L;
	expected.data[8] = 1.1043411977337285L;
	expected.data[9] = 0.8169111628514665L;
	expected.data[10] = 0.6786490489588681L;
	expected.data[11] = 0.8786916489338669L;
	expected.data[12] = 0.9515847749097763L;
	expected.data[13] = 0.8241524511649997L;
	expected.data[14] = 0.9631792701548485L;
	expected.data[15] = 0.8604034722369528L;
	expected.data[16] = 1.0771139253107898L;
	expected.data[17] = 0.7150848442283582L;
	expected.data[18] = 0.8211647222256067L;
	expected.data[19] = 1.0060282281355237L;
	expected.data[20] = 0.9421113863958565L;
	expected.data[21] = 0.726764144804287L;
	expected.data[22] = 0.6882001796917159L;
	expected.data[23] = 0.8276915902280734L;
	expected.data[24] = 0.9241844409593405L;
	expected.data[25] = 0.8864152298827196L;
	expected.data[26] = 0.9304381380159433L;
	expected.data[27] = 0.6555727697153041L;
	expected.data[28] = 0.9201400332846313L;
	expected.data[29] = 0.7150848442283582L;
	expected.data[30] = 0.7930125433710051L;
	expected.data[31] = 1.0060282281355237L;
	expected.data[32] = 0.8844165624273322L;
	expected.data[33] = 0.6933911940503907L;
	expected.data[34] = 0.6734211143506279L;
	expected.data[35] = 0.8786916489338669L;
	expected.data[36] = 0.9515847749097763L;
	expected.data[37] = 0.9771407386012378L;
	expected.data[38] = 0.876396892054303L;
	expected.data[39] = 0.8602933043102555L;
	expected.data[40] = 0.8570896806983546L;
	expected.data[41] = 0.9511528631876855L;
	expected.data[42] = 1.0700991511626783L;
	expected.data[43] = 0.8543145861129054L;
	expected.data[44] = 0.9421113863958565L;
	expected.data[45] = 0.726764144804287L;
	expected.data[46] = 0.6882001796917159L;
	expected.data[47] = 0.8276915902280734L;
	expected.data[48] = 0.9303386353673364L;
	expected.data[49] = 0.8183124686033922L;
	expected.data[50] = 0.7378075631723987L;
	expected.data[51] = 0.7074759836873623L;
	expected.data[52] = 1.1932372886062026L;
	expected.data[53] = 0.9326178899409782L;
	expected.data[54] = 0.9429550548933133L;
	expected.data[55] = 0.9976159306917647L;
	expected.data[56] = 0.9440562995484425L;
	expected.data[57] = 0.6014612280348931L;
	expected.data[58] = 0.42161482558296315L;
	expected.data[59] = 0.4601125735064131L;
	expected.data[60] = 0.46046964370440424L;
	expected.data[61] = 0.46285269782253646L;
	expected.data[62] = 0.43493991254521847L;
	expected.data[63] = 0.336831595591884L;
	expected.data[64] = 0.3420675286886336L;
	expected.data[65] = 0.27346394589175826L;
	expected.data[66] = 0.3478389011780247L;
	expected.data[67] = 0.3878554014500162L;
	expected.data[68] = 0.33146231327970355L;
	expected.data[69] = 0.2982910651335166L;
	expected.data[70] = 0.27020464161951385L;
	expected.data[71] = 0.4601125735064131L;
	expected.data[72] = 0.46046964370440424L;
	expected.data[73] = 0.46285269782253646L;
	expected.data[74] = 0.43493991254521847L;
	expected.data[75] = 0.336831595591884L;
	expected.data[76] = 0.3420675286886336L;
	expected.data[77] = 0.27346394589175826L;
	expected.data[78] = 0.3478389011780247L;
	expected.data[79] = 0.3878554014500162L;
	expected.data[80] = 0.33146231327970355L;
	expected.data[81] = 0.2982910651335166L;
	expected.data[82] = 0.27020464161951385L;

	expected.index = (unsigned long*) calloc(expected.length, sizeof(unsigned long));
	expected.index[0] = 24;
	expected.index[1] = 49;
	expected.index[2] = 50;
	expected.index[3] = 51;
	expected.index[4] = 76;
	expected.index[5] = 29;
	expected.index[6] = 30;
	expected.index[7] = 31;
	expected.index[8] = 32;
	expected.index[9] = 33;
	expected.index[10] = 34;
	expected.index[11] = 35;
	expected.index[12] = 36;
	expected.index[13] = 1;
	expected.index[14] = 74;
	expected.index[15] = 75;
	expected.index[16] = 28;
	expected.index[17] = 29;
	expected.index[18] = 30;
	expected.index[19] = 31;
	expected.index[20] = 44;
	expected.index[21] = 45;
	expected.index[22] = 46;
	expected.index[23] = 47;
	expected.index[24] = 60;
	expected.index[25] = 61;
	expected.index[26] = 62;
	expected.index[27] = 63;
	expected.index[28] = 4;
	expected.index[29] = 17;
	expected.index[30] = 6;
	expected.index[31] = 19;
	expected.index[32] = 80;
	expected.index[33] = 81;
	expected.index[34] = 82;
	expected.index[35] = 11;
	expected.index[36] = 12;
	expected.index[37] = 13;
	expected.index[38] = 62;
	expected.index[39] = 75;
	expected.index[40] = 76;
	expected.index[41] = 5;
	expected.index[42] = 18;
	expected.index[43] = 67;
	expected.index[44] = 20;
	expected.index[45] = 21;
	expected.index[46] = 22;
	expected.index[47] = 23;
	expected.index[48] = 24;
	expected.index[49] = 1;
	expected.index[50] = 2;
	expected.index[51] = 3;
	expected.index[52] = 64;
	expected.index[53] = 65;
	expected.index[54] = 78;
	expected.index[55] = 79;
	expected.index[56] = 80;
	expected.index[57] = 69;
	expected.index[58] = 70;
	expected.index[59] = 71;
	expected.index[60] = 72;
	expected.index[61] = 73;
	expected.index[62] = 74;
	expected.index[63] = 75;
	expected.index[64] = 76;
	expected.index[65] = 77;
	expected.index[66] = 78;
	expected.index[67] = 79;
	expected.index[68] = 80;
	expected.index[69] = 81;
	expected.index[70] = 82;
	expected.index[71] = 59;
	expected.index[72] = 60;
	expected.index[73] = 61;
	expected.index[74] = 62;
	expected.index[75] = 63;
	expected.index[76] = 64;
	expected.index[77] = 65;
	expected.index[78] = 66;
	expected.index[79] = 67;
	expected.index[80] = 68;
	expected.index[81] = 69;
	expected.index[82] = 70;


    // top-level unit tests for elementwise_minimum
    
    // top-level unit tests for stamp
    MatrixProfile result = stamp(ts, 10, 3);

    printMatrixProfile("expected", expected);
    printMatrixProfile("result", result);

	EXPECT_EQ(expected.length, result.length);
	for (unsigned long i = 0; i < expected.length; i++) {
		EXPECT_NEAR((double)expected.data[i], (double)result.data[i], 0.0000000000033);
		EXPECT_EQ(expected.index[i], result.index[i]);
	}

    // clean up
    free(ts.data);
    free(expected.data);
    free(expected.index);
    free(result.data);
    free(result.index);

}


