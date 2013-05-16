// hillcalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "track.h"
#include "prog_params.h"

int _tmain(int argc, _TCHAR* argv[])
{
	parse_params(argc, argv);

	track trk;

	trk.fromGarminText(g_params.source);
	float ascendStupid = trk.calcAscendStupid();
	float ascendHills = trk.calcHills();

	trk.filterSmooth();
	float ascendStupidFilt = trk.calcAscendStupid();
	float ascendHillsFilt = trk.calcHills();


	printf("Total ascend for %s, Hills epsilon: %f, Smooth coeff: %f\n", g_params.source, g_params.hills_epsilon, g_params.smooth_coeff);

	printf("Ascend by stupid method: %f\n", ascendStupid);
	printf("Ascend by hills calc: %f\n", ascendHills);

	printf("After filtering...\n");

	printf("Ascend by stupid method: %f\n", ascendStupidFilt);
	printf("Ascend by hills calc: %f\n", ascendHillsFilt);

	return 0;
}

