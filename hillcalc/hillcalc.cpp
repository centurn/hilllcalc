// hillcalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "track.h"


int _tmain(int argc, _TCHAR* argv[])
{
	track trk;
	float ascendStupid;

	trk.fromGarminText("D:\\temp\\2012_02_29.txt");
	ascendStupid = trk.calcAscendStupid();

	return 0;
}

