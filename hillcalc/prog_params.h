#include "stdafx.h"

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

extern prog_params g_params;

extern void parse_params(int argc, _TCHAR* argv[]);
