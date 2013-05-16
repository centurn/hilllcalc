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

	return 0;
}

