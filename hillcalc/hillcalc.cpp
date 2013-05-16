// hillcalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "track.h"

struct prog_params{
	const char* source;
	float       hills_epsilon;
	float		smooth_coeff;
	bool        log;
	prog_params()
		: hills_epsilon(3.5)
		, smooth_coeff(0.5)
		, log(false)
	{};
};

prog_params g_params;

#pragma warning(disable: 4996)
static void parse_params(int argc, _TCHAR* argv[]){
	for(--argc, ++argv; argc; --argc, ++argv){
		if(argv[0][0] == '-'){
			switch(argv[0][1]){
			case 'e':
				sscanf(&argv[0][2], "%f", &g_params.hills_epsilon); break;
			case 'k':
				sscanf(&argv[0][2], "%f", &g_params.smooth_coeff); break;
			case 'l':
				g_params.log = true; break;
			default:
				printf("Unrecognized param: %s\n", &argv[0][0]);
				break;
			}
		}else{
			g_params.source = *argv;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	parse_params(argc, argv);

	track trk;

	if(argc < 1)
		printf(" usage:\n hillcalc <filename> [hill epsilon]");

	trk.fromGarminText(""/*argv[0]*/);
	float ascendStupid = trk.calcAscendStupid();
	float ascendHills = trk.calcHills();

	return 0;
}

