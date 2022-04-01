#include <gtest/gtest.h>
#include "distance_profile.h"
#include "sliding_dot_product.h"


TEST(DistanceProfileTest, test_distance_profile) {
    
    /* Test for distance_profile:

    DoubleArray calculate_distance_profile(const DoubleArray& query_segment, const DoubleArray& time_series);

    */

    DoubleArray ts2;
    ts2.length = 92;
    ts2.data = (double*) calloc(ts2.length, sizeof(double));
    ts2.data[0] = 12;
    ts2.data[1] = 118;
    ts2.data[2] = 132;
    ts2.data[3] = 129;
    ts2.data[4] = 121;
    ts2.data[5] = 135;
    ts2.data[6] = 148;
    ts2.data[7] = 148;
    ts2.data[8] = 136;
    ts2.data[9] = 119;
    ts2.data[10] = 104;
    ts2.data[11] = 118;
    ts2.data[12] = 115;
    ts2.data[13] = 126;
    ts2.data[14] = 141;
    ts2.data[15] = 135;
    ts2.data[16] = 125;
    ts2.data[17] = 149;
    ts2.data[18] = 170;
    ts2.data[19] = 170;
    ts2.data[20] = 158;
    ts2.data[21] = 133;
    ts2.data[22] = 114;
    ts2.data[23] = 140;
    ts2.data[24] = 145;
    ts2.data[25] = 150;
    ts2.data[26] = 178;
    ts2.data[27] = 163;
    ts2.data[28] = 172;
    ts2.data[29] = 178;
    ts2.data[30] = 199;
    ts2.data[31] = 199;
    ts2.data[32] = 184;
    ts2.data[33] = 162;
    ts2.data[34] = 146;
    ts2.data[35] = 166;
    ts2.data[36] = 171;
    ts2.data[37] = 180;
    ts2.data[38] = 193;
    ts2.data[39] = 181;
    ts2.data[40] = 183;
    ts2.data[41] = 218;
    ts2.data[42] = 230;
    ts2.data[43] = 242;
    ts2.data[44] = 209;
    ts2.data[45] = 191;
    ts2.data[46] = 172;
    ts2.data[47] = 194;
    ts2.data[48] = 196;
    ts2.data[49] = 196;
    ts2.data[50] = 236;
    ts2.data[51] = 235;
    ts2.data[52] = 229;
    ts2.data[53] = 243;
    ts2.data[54] = 264;
    ts2.data[55] = 272;
    ts2.data[56] = 237;
    ts2.data[57] = 211;
    ts2.data[58] = 180;
    ts2.data[59] = 201;
    ts2.data[60] = 204;
    ts2.data[61] = 188;
    ts2.data[62] = 235;
    ts2.data[63] = 227;
    ts2.data[64] = 234;
    ts2.data[65] = 264;
    ts2.data[66] = 302;
    ts2.data[67] = 293;
    ts2.data[68] = 259;
    ts2.data[69] = 229;
    ts2.data[70] = 203;
    ts2.data[71] = 229;
    ts2.data[72] = 242;
    ts2.data[73] = 233;
    ts2.data[74] = 267;
    ts2.data[75] = 269;
    ts2.data[76] = 270;
    ts2.data[77] = 315;
    ts2.data[78] = 364;
    ts2.data[79] = 347;
    ts2.data[80] = 312;
    ts2.data[81] = 274;
    ts2.data[82] = 237;
    ts2.data[83] = 278;
    ts2.data[84] = 284;
    ts2.data[85] = 277;
    ts2.data[86] = 317;
    ts2.data[87] = 313;
    ts2.data[88] = 318;
    ts2.data[89] = 374;
    ts2.data[90] = 413;
    ts2.data[91] = 405;


    DoubleArray qs2;
    qs2.length = 11;
    qs2.data = (double*) calloc(qs2.length, sizeof(double));
    qs2.data[0] = 115;
    qs2.data[1] = 126;
    qs2.data[2] = 141;
    qs2.data[3] = 135;
    qs2.data[4] = 125;
    qs2.data[5] = 149;
    qs2.data[6] = 170;
    qs2.data[7] = 170;
    qs2.data[8] = 158;
    qs2.data[9] = 133;
    qs2.data[10] = 114;


    DoubleArray expected2;
    expected2.length = 82;
    expected2.data = (double*) calloc(expected2.length, sizeof(double));
    expected2.data[0] = 2.609129798276973;
    expected2.data[1] = 3.247474463287497;
    expected2.data[2] = 4.963778973129025;
    expected2.data[3] = 5.677939941367938;
    expected2.data[4] = 5.970549972451267;
    expected2.data[5] = 5.826055005206217;
    expected2.data[6] = 5.193120075912781;
    expected2.data[7] = 5.108505247593514;
    expected2.data[8] = 5.032564733253847;
    expected2.data[9] = 4.744807794445634;
    expected2.data[10] = 4.211821343731478;
    expected2.data[11] = 2.7243405032943464;
    expected2.data[12] = 3.551356580201681e-07;
    expected2.data[13] = 3.112653755797463;
    expected2.data[14] = 4.981923811253705;
    expected2.data[15] = 5.524651612994309;
    expected2.data[16] = 5.71066956718392;
    expected2.data[17] = 5.456583873559318;
    expected2.data[18] = 4.997581485080036;
    expected2.data[19] = 4.766531548364473;
    expected2.data[20] = 4.536117387854447;
    expected2.data[21] = 4.152295221396132;
    expected2.data[22] = 3.720593453248237;
    expected2.data[23] = 2.4735790950525685;
    expected2.data[24] = 1.051560525456292;
    expected2.data[25] = 3.1273279095397846;
    expected2.data[26] = 5.0790841636433735;
    expected2.data[27] = 5.738999213439761;
    expected2.data[28] = 5.971128959974927;
    expected2.data[29] = 5.407649137565428;
    expected2.data[30] = 4.963220378606742;
    expected2.data[31] = 5.179140817732341;
    expected2.data[32] = 5.045633107386387;
    expected2.data[33] = 4.710179450931178;
    expected2.data[34] = 3.8779508855330582;
    expected2.data[35] = 2.303746512377498;
    expected2.data[36] = 0.95994437239504;
    expected2.data[37] = 3.218769679769625;
    expected2.data[38] = 4.740420036675623;
    expected2.data[39] = 5.230713210094094;
    expected2.data[40] = 5.711976325333525;
    expected2.data[41] = 5.824514724284961;
    expected2.data[42] = 5.371533860818264;
    expected2.data[43] = 4.997650650696966;
    expected2.data[44] = 4.399242654686056;
    expected2.data[45] = 4.129186815390604;
    expected2.data[46] = 3.6307781608875174;
    expected2.data[47] = 2.495141350798362;
    expected2.data[48] = 1.369220392900506;
    expected2.data[49] = 3.1472081299581323;
    expected2.data[50] = 5.022443518437396;
    expected2.data[51] = 5.479233515566667;
    expected2.data[52] = 5.84687289969472;
    expected2.data[53] = 5.860345833934739;
    expected2.data[54] = 5.7352549749491315;
    expected2.data[55] = 5.706444447808072;
    expected2.data[56] = 5.255268136027846;
    expected2.data[57] = 4.557375366335473;
    expected2.data[58] = 3.7312953798816437;
    expected2.data[59] = 2.484937910647551;
    expected2.data[60] = 1.1938028502673246;
    expected2.data[61] = 3.004559246543958;
    expected2.data[62] = 4.9374711997578355;
    expected2.data[63] = 5.398827345051345;
    expected2.data[64] = 5.685801483681174;
    expected2.data[65] = 5.7443660286988685;
    expected2.data[66] = 5.536733441171743;
    expected2.data[67] = 5.437290492329577;
    expected2.data[68] = 5.146926030493165;
    expected2.data[69] = 4.526932426163664;
    expected2.data[70] = 3.697491718216762;
    expected2.data[71] = 2.415835092531521;
    expected2.data[72] = 1.0373793114988235;
    expected2.data[73] = 3.0375217900827445;
    expected2.data[74] = 4.8116468265067125;
    expected2.data[75] = 5.305692565054214;
    expected2.data[76] = 5.605576634307004;
    expected2.data[77] = 5.706587756284229;
    expected2.data[78] = 5.519060820380161;
    expected2.data[79] = 5.500727919732985;
    expected2.data[80] = 5.156250283604572;
    expected2.data[81] = 4.502456669628784;

    // calculate_distance_profile
    DoubleArray result2 = calculate_distance_profile(qs2, ts2);


    printf("\nCompare computed distance_profile result2 to expected2 distance_profile values\n");
    printDoubleArray("expected2", expected2);


	// Ensure result matches expected
	EXPECT_EQ(result2.length, expected2.length);
	for (unsigned long i = 0; i < result2.length; i++) {
		EXPECT_DOUBLE_EQ(result2.data[i], expected2.data[i]);
		//EXPECT_NEAR(result2.data[i], expected2.data[i], 0.000000000003);
	}

    // clean up
    free(ts2.data);
    free(qs2.data);
    free(result2.data);
    free(expected2.data);

}


