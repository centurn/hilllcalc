#include "prog_params.h"

prog_params g_params;

#pragma warning(disable: 4996)
void parse_params(int argc, _TCHAR* argv[]){
	for(--argc, ++argv; argc; --argc, ++argv){
		if(argv[0][0] == '-'){
			switch(argv[0][1]){
			case 'e':
				sscanf(&argv[0][2], "%f", &g_params.hills_epsilon); break;
			case 'k':
				float temp;
				sscanf(&argv[0][2], "%f", &temp); 
				if(temp < 0 || temp > 1)
					printf("Smooth coeff should be between 1 and 0. Ignored\n");
				else 
					g_params.smooth_coeff = temp;
				break;
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
