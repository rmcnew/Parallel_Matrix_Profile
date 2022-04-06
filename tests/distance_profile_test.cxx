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

    LongDoubleArray ts2;
    ts2.length = 126;
    ts2.data = (long double*) calloc(ts2.length, sizeof(long double));
    ts2.data[0] = 811.659973L;
    ts2.data[1] = 816.119995L;
    ts2.data[2] = 796.219971L;
    ts2.data[3] = 798.150024L;
    ts2.data[4] = 787.380005L;
    ts2.data[5] = 781.299988L;
    ts2.data[6] = 714.5L;
    ts2.data[7] = 698.840027L;
    ts2.data[8] = 742.02002L;
    ts2.data[9] = 682.219971L;
    ts2.data[10] = 675.5L;
    ts2.data[11] = 718.429993L;
    ts2.data[12] = 686.440002L;
    ts2.data[13] = 653.200012L;
    ts2.data[14] = 621.440002L;
    ts2.data[15] = 597.950012L;
    ts2.data[16] = 563.0L;
    ts2.data[17] = 673.580017L;
    ts2.data[18] = 668.059998L;
    ts2.data[19] = 699.599976L;
    ts2.data[20] = 693.72998L;
    ts2.data[21] = 707.940002L;
    ts2.data[22] = 676.880005L;
    ts2.data[23] = 701.809998L;
    ts2.data[24] = 653.159973L;
    ts2.data[25] = 654.869995L;
    ts2.data[26] = 670.0L;
    ts2.data[27] = 662.159973L;
    ts2.data[28] = 630.27002L;
    ts2.data[29] = 640.390015L;
    ts2.data[30] = 618.710022L;
    ts2.data[31] = 611.289978L;
    ts2.data[32] = 635.619995L;
    ts2.data[33] = 667.929993L;
    ts2.data[34] = 661.75L;
    ts2.data[35] = 691.049988L;
    ts2.data[36] = 691.619995L;
    ts2.data[37] = 670.969971L;
    ts2.data[38] = 683.799988L;
    ts2.data[39] = 677.02002L;
    ts2.data[40] = 701.97998L;
    ts2.data[41] = 762.320007L;
    ts2.data[42] = 732.22998L;
    ts2.data[43] = 738.849976L;
    ts2.data[44] = 739.780029L;
    ts2.data[45] = 714.630005L;
    ts2.data[46] = 718.98999L;
    ts2.data[47] = 744.119995L;
    ts2.data[48] = 719.690002L;
    ts2.data[49] = 729.400024L;
    ts2.data[50] = 738.200012L;
    ts2.data[51] = 704.73999L;
    ts2.data[52] = 694.400024L;
    ts2.data[53] = 677.0L;
    ts2.data[54] = 709.440002L;
    ts2.data[55] = 684.900024L;
    ts2.data[56] = 673.599976L;
    ts2.data[57] = 670.940002L;
    ts2.data[58] = 663.539978L;
    ts2.data[59] = 672.369995L;
    ts2.data[60] = 629.039978L;
    ts2.data[61] = 617.200012L;
    ts2.data[62] = 589.890015L;
    ts2.data[63] = 571.690002L;
    ts2.data[64] = 589.73999L;
    ts2.data[65] = 576.830017L;
    ts2.data[66] = 577.869995L;
    ts2.data[67] = 563.460022L;
    ts2.data[68] = 586.780029L;
    ts2.data[69] = 580.880005L;
    ts2.data[70] = 606.440002L;
    ts2.data[71] = 604.690002L;
    ts2.data[72] = 619.130005L;
    ts2.data[73] = 630.849976L;
    ts2.data[74] = 625.219971L;
    ts2.data[75] = 623.900024L;
    ts2.data[76] = 605.119995L;
    ts2.data[77] = 572.840027L;
    ts2.data[78] = 599.049988L;
    ts2.data[79] = 605.130005L;
    ts2.data[80] = 603.590027L;
    ts2.data[81] = 598.780029L;
    ts2.data[82] = 610.119995L;
    ts2.data[83] = 609.890015L;
    ts2.data[84] = 617.690002L;
    ts2.data[85] = 599.359985L;
    ts2.data[86] = 604.869995L;
    ts2.data[87] = 616.599976L;
    ts2.data[88] = 623.309998L;
    ts2.data[89] = 620.830017L;
    ts2.data[90] = 623.710022L;
    ts2.data[91] = 656.570007L;
    ts2.data[92] = 679.820007L;
    ts2.data[93] = 671.869995L;
    ts2.data[94] = 688.719971L;
    ts2.data[95] = 680.76001L;
    ts2.data[96] = 679.700012L;
    ts2.data[97] = 677.919983L;
    ts2.data[98] = 678.900024L;
    ts2.data[99] = 659.580017L;
    ts2.data[100] = 644.650024L;
    ts2.data[101] = 652.809998L;
    ts2.data[102] = 656.950012L;
    ts2.data[103] = 685.700012L;
    ts2.data[104] = 668.539978L;
    ts2.data[105] = 653.380005L;
    ts2.data[106] = 650.599976L;
    ts2.data[107] = 644.219971L;
    ts2.data[108] = 646.219971L;
    ts2.data[109] = 660.5L;
    ts2.data[110] = 655.289978L;
    ts2.data[111] = 649.26001L;
    ts2.data[112] = 643.380005L;
    ts2.data[113] = 657.619995L;
    ts2.data[114] = 644.780029L;
    ts2.data[115] = 646.97998L;
    ts2.data[116] = 677.349976L;
    ts2.data[117] = 687.200012L;
    ts2.data[118] = 709.669983L;
    ts2.data[119] = 709.73999L;
    ts2.data[120] = 710.919983L;
    ts2.data[121] = 714.630005L;
    ts2.data[122] = 699.099976L;
    ts2.data[123] = 713.76001L;
    ts2.data[124] = 709.98999L;
    ts2.data[125] = 707.820007L;

    LongDoubleArray qs2;
    qs2.length = 10;
    qs2.data = (long double*) &(ts2.data[40]);

    LongDoubleArray expected2;
    expected2.length = 117;
    expected2.data = (long double*) calloc(expected2.length, sizeof(long double));
	expected2.data[0] = 4.296523339090426L;
	expected2.data[1] = 3.8502954261410163L;
	expected2.data[2] = 4.1615797274014L;
	expected2.data[3] = 4.674424131869327L;
	expected2.data[4] = 3.937113626365001L;
	expected2.data[5] = 4.809974490675176L;
	expected2.data[6] = 4.671595073229344L;
	expected2.data[7] = 3.877969108347787L;
	expected2.data[8] = 4.5059244786436805L;
	expected2.data[9] = 4.487751337621087L;
	expected2.data[10] = 3.381581578978703L;
	expected2.data[11] = 4.6767627283952535L;
	expected2.data[12] = 5.210218846827372L;
	expected2.data[13] = 5.1782708953697325L;
	expected2.data[14] = 4.875216183625244L;
	expected2.data[15] = 5.080724733112386L;
	expected2.data[16] = 3.0040571325530294L;
	expected2.data[17] = 4.525781235788322L;
	expected2.data[18] = 3.750951181965917L;
	expected2.data[19] = 3.9204157671537936L;
	expected2.data[20] = 3.718378986774067L;
	expected2.data[21] = 5.0325650198327105L;
	expected2.data[22] = 3.6696235909324044L;
	expected2.data[23] = 4.817989637408735L;
	expected2.data[24] = 4.385004300344586L;
	expected2.data[25] = 3.892607889427903L;
	expected2.data[26] = 4.322302540476948L;
	expected2.data[27] = 5.361942441763805L;
	expected2.data[28] = 4.754845046599998L;
	expected2.data[29] = 4.9744399304880185L;
	expected2.data[30] = 5.079270541773944L;
	expected2.data[31] = 4.245169318124926L;
	expected2.data[32] = 4.1118705095116885L;
	expected2.data[33] = 4.841238175436074L;
	expected2.data[34] = 3.9077473773969578L;
	expected2.data[35] = 4.971705565491427L;
	expected2.data[36] = 5.371753173033065L;
	expected2.data[37] = 4.320005560023607L;
	expected2.data[38] = 4.733300837242247L;
	expected2.data[39] = 4.167717531943037L;
	expected2.data[40] = 6.695116764136823e-06L;
	expected2.data[41] = 5.407607290496536L;
	expected2.data[42] = 4.663794753123552L;
	expected2.data[43] = 3.8683499916660113L;
	expected2.data[44] = 4.973797838784662L;
	expected2.data[45] = 4.291202539508706L;
	expected2.data[46] = 3.6728642323791787L;
	expected2.data[47] = 4.18816674087825L;
	expected2.data[48] = 3.9632055822936225L;
	expected2.data[49] = 4.399147973785972L;
	expected2.data[50] = 4.783400168677063L;
	expected2.data[51] = 4.37488458203412L;
	expected2.data[52] = 4.290256076051438L;
	expected2.data[53] = 3.9303842701333997L;
	expected2.data[54] = 4.495897019385939L;
	expected2.data[55] = 4.161048308290633L;
	expected2.data[56] = 4.184117004112138L;
	expected2.data[57] = 4.0271345023176846L;
	expected2.data[58] = 4.026740810210083L;
	expected2.data[59] = 4.859359722222767L;
	expected2.data[60] = 4.732614114014479L;
	expected2.data[61] = 4.829148854940048L;
	expected2.data[62] = 5.139455629544939L;
	expected2.data[63] = 4.194010963233276L;
	expected2.data[64] = 5.037447699127474L;
	expected2.data[65] = 4.864991049652353L;
	expected2.data[66] = 4.953312506033825L;
	expected2.data[67] = 4.391679298778698L;
	expected2.data[68] = 4.79758223611009L;
	expected2.data[69] = 3.7150485242850517L;
	expected2.data[70] = 4.711388280842395L;
	expected2.data[71] = 3.34858524826215L;
	expected2.data[72] = 3.2787216081064186L;
	expected2.data[73] = 4.654776740652412L;
	expected2.data[74] = 4.87679213900337L;
	expected2.data[75] = 5.0135807472107095L;
	expected2.data[76] = 5.633678684795519L;
	expected2.data[77] = 3.4495834140761588L;
	expected2.data[78] = 4.75559949648462L;
	expected2.data[79] = 4.883114748945747L;
	expected2.data[80] = 4.373071957290825L;
	expected2.data[81] = 3.893096989655213L;
	expected2.data[82] = 4.839324865786753L;
	expected2.data[83] = 4.720756018548161L;
	expected2.data[84] = 4.888319386975787L;
	expected2.data[85] = 4.519981940436002L;
	expected2.data[86] = 4.870928963211103L;
	expected2.data[87] = 4.7801086081920054L;
	expected2.data[88] = 4.766388930528832L;
	expected2.data[89] = 4.697295561395487L;
	expected2.data[90] = 3.780185272966993L;
	expected2.data[91] = 3.2907718492796914L;
	expected2.data[92] = 4.5533637894684125L;
	expected2.data[93] = 3.894664116590736L;
	expected2.data[94] = 4.161297937853456L;
	expected2.data[95] = 4.216777860925432L;
	expected2.data[96] = 4.125715565846557L;
	expected2.data[97] = 4.6201327039945745L;
	expected2.data[98] = 5.527273053376387L;
	expected2.data[99] = 4.787694724986535L;
	expected2.data[100] = 3.6885564647557936L;
	expected2.data[101] = 4.102874445834441L;
	expected2.data[102] = 2.6353614058011483L;
	expected2.data[103] = 4.9215233141632035L;
	expected2.data[104] = 5.562792944049909L;
	expected2.data[105] = 5.062417434436585L;
	expected2.data[106] = 4.016156975778977L;
	expected2.data[107] = 4.394363685645665L;
	expected2.data[108] = 4.505737944914674L;
	expected2.data[109] = 4.508517420490538L;
	expected2.data[110] = 4.785232064280431L;
	expected2.data[111] = 4.918891468517808L;
	expected2.data[112] = 4.683404508739847L;
	expected2.data[113] = 5.090947757648563L;
	expected2.data[114] = 4.620221885284223L;
	expected2.data[115] = 4.184052934512047L;
	expected2.data[116] = 4.110118656643019L;

    // calculate_distance_profile
    LongDoubleArray result2 = calculate_distance_profile(qs2, ts2);


    //printf("\nCompare computed distance_profile result to expected distance_profile values\n");
    //printLongDoubleArray("expected2", expected2);


	// Ensure result matches expected
	EXPECT_EQ(result2.length, expected2.length);
	for (unsigned long i = 0; i < result2.length; i++) {
        if (i == 40) {
            continue;  // apply the exclusion zone:  query segment starts at index 40
        }
		EXPECT_NEAR((double)expected2.data[i], (double)result2.data[i], 0.0000000000033);
	}

    // clean up
    free(ts2.data);
    free(result2.data);
    free(expected2.data);
}


