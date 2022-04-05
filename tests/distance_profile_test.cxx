#include <gtest/gtest.h>
#include "distance_profile.h"
#include "sliding_dot_product.h"


TEST(DistanceProfileTest, test_distance_profile) {
    
    /* Test for distance_profile:

    LongDoubleArray calculate_distance_profile(const LongDoubleArray& query_segment, const LongDoubleArray& time_series);

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


    LongDoubleArray qs;
    qs.length = 11;
    qs.data = (long double*) &(ts.data[12]);
    

    LongDoubleArray expected;
    expected.length = 82;
    expected.data = (long double*) calloc(expected.length, sizeof(long double));
    expected.data[0] = 2.609129798276973;
    expected.data[1] = 3.247474463287497;
    expected.data[2] = 4.963778973129025;
    expected.data[3] = 5.677939941367938;
    expected.data[4] = 5.970549972451267;
    expected.data[5] = 5.826055005206217;
    expected.data[6] = 5.193120075912781;
    expected.data[7] = 5.108505247593514;
    expected.data[8] = 5.032564733253847;
    expected.data[9] = 4.744807794445634;
    expected.data[10] = 4.211821343731478;
    expected.data[11] = 2.7243405032943464;
    expected.data[12] = 3.551356580201681e-07;  // This should be zero since it is the start of the query_segment
    expected.data[13] = 3.112653755797463;
    expected.data[14] = 4.981923811253705;
    expected.data[15] = 5.524651612994309;
    expected.data[16] = 5.71066956718392;
    expected.data[17] = 5.456583873559318;
    expected.data[18] = 4.997581485080036;
    expected.data[19] = 4.766531548364473;
    expected.data[20] = 4.536117387854447;
    expected.data[21] = 4.152295221396132;
    expected.data[22] = 3.720593453248237;
    expected.data[23] = 2.4735790950525685;
    expected.data[24] = 1.051560525456292;
    expected.data[25] = 3.1273279095397846;
    expected.data[26] = 5.0790841636433735;
    expected.data[27] = 5.738999213439761;
    expected.data[28] = 5.971128959974927;
    expected.data[29] = 5.407649137565428;
    expected.data[30] = 4.963220378606742;
    expected.data[31] = 5.179140817732341;
    expected.data[32] = 5.045633107386387;
    expected.data[33] = 4.710179450931178;
    expected.data[34] = 3.8779508855330582;
    expected.data[35] = 2.303746512377498;
    expected.data[36] = 0.95994437239504;
    expected.data[37] = 3.218769679769625;
    expected.data[38] = 4.740420036675623;
    expected.data[39] = 5.230713210094094;
    expected.data[40] = 5.711976325333525;
    expected.data[41] = 5.824514724284961;
    expected.data[42] = 5.371533860818264;
    expected.data[43] = 4.997650650696966;
    expected.data[44] = 4.399242654686056;
    expected.data[45] = 4.129186815390604;
    expected.data[46] = 3.6307781608875174;
    expected.data[47] = 2.495141350798362;
    expected.data[48] = 1.369220392900506;
    expected.data[49] = 3.1472081299581323;
    expected.data[50] = 5.022443518437396;
    expected.data[51] = 5.479233515566667;
    expected.data[52] = 5.84687289969472;
    expected.data[53] = 5.860345833934739;
    expected.data[54] = 5.7352549749491315;
    expected.data[55] = 5.706444447808072;
    expected.data[56] = 5.255268136027846;
    expected.data[57] = 4.557375366335473;
    expected.data[58] = 3.7312953798816437;
    expected.data[59] = 2.484937910647551;
    expected.data[60] = 1.1938028502673246;
    expected.data[61] = 3.004559246543958;
    expected.data[62] = 4.9374711997578355;
    expected.data[63] = 5.398827345051345;
    expected.data[64] = 5.685801483681174;
    expected.data[65] = 5.7443660286988685;
    expected.data[66] = 5.536733441171743;
    expected.data[67] = 5.437290492329577;
    expected.data[68] = 5.146926030493165;
    expected.data[69] = 4.526932426163664;
    expected.data[70] = 3.697491718216762;
    expected.data[71] = 2.415835092531521;
    expected.data[72] = 1.0373793114988235;
    expected.data[73] = 3.0375217900827445;
    expected.data[74] = 4.8116468265067125;
    expected.data[75] = 5.305692565054214;
    expected.data[76] = 5.605576634307004;
    expected.data[77] = 5.706587756284229;
    expected.data[78] = 5.519060820380161;
    expected.data[79] = 5.500727919732985;
    expected.data[80] = 5.156250283604572;
    expected.data[81] = 4.502456669628784;

    // calculate_distance_profile
    LongDoubleArray result = calculate_distance_profile(qs, ts);


    //printf("\nCompare computed distance_profile result to expected distance_profile values\n");
    //printLongDoubleArray("expected", expected);


	// Ensure result matches expected
	EXPECT_EQ(result.length, expected.length);
	for (unsigned long i = 0; i < result.length; i++) {
        if (i == 12) {
            continue;  // apply the exclusion zone:  query segment starts at index 12
        }
		//EXPECT_DOUBLE_EQ(expected.data[i], result.data[i]);
        //printf("%lu:  expected: %Le,  result: %Le\n", i, expected.data[i], result.data[i]);
		EXPECT_NEAR((double)expected.data[i], (double)result.data[i], 0.000000000003);
	}

    // clean up
    free(ts.data);
    free(result.data);
    free(expected.data);

}


