#include "track.h"
#include "prog_params.h"

#include <io.h>
#include <fstream>
#include <iostream>

static char const* lineskip(char const* str){
	const char* result = strchr(str, '\n');
	return result? result+1: "";
}

#pragma warning(disable: 4996)
void track::fromGarminText(char const* file){
	FILE* f = fopen(file, "r");
	if(f){
		fseek(f, 0, SEEK_END);
		long size = ftell(f);
		rewind(f);

		std::vector<char> buffer;
		buffer.resize(size+1);
		size = fread(&buffer[0], 1, size, f);
		fclose(f);
		buffer[size] = 0;

		const char* pos = strstr(&buffer[0], "trkpt\n");
		if(!pos)
			return;

		pos = lineskip(lineskip(pos));

		while(*pos){
			trkpoint temp;
			sscanf(pos, "%u %u %f %f %f", &temp.ID, &temp.trksegID, &temp.lat, &temp.lon, &temp.ele);
			pos = lineskip(pos);
			m_data.push_back(temp);
		}
	}
}

float track::calcAscendStupid() const{
	if(m_data.size() < 2)
		return 0;

	float result = 0;
	float prev = m_data[0].ele; 
	for(int i = 1, end = m_data.size(); i< end; ++i){
		float diff = m_data[i].ele - prev;
		if(diff > 0.1f)
			result += diff;
		prev = m_data[i].ele;
	}

	return result;
}

float track::calcHills() const{
	if(m_data.size() < 2)
		return 0;

	float result = 0;
	float prev_extremum = m_data[0].ele;
	float cur_extremum = 0;

	int direction = 0;// Altitude change. 0 for down, 1 for up
	int i = 1, end = m_data.size();
	
	// Initial set up. We don't know if it's uphill or downhill yet
	for(; i < end; ++i){
		float diff = m_data[i].ele - prev_extremum;
		if(fabs(diff) > g_params.hills_epsilon){
			cur_extremum = m_data[i].ele;
			direction = !(*((uint*)(&diff))&(1<<31));// That masks sign bit in floating point. Positive diff means we are doing up
			break;
		}
	}

	for(++i; i < end; ++i){
		float cur = m_data[i].ele;

		// Check if we continue deeper in the same direction (up or down)
		if(direction? cur > cur_extremum: cur < cur_extremum){
			cur_extremum = cur;
			continue;
		}

		// Direction changed. If the change is deep enough, it's time to go for next hill
		float diff = m_data[i].ele - cur_extremum;
		if(fabs(diff) > g_params.hills_epsilon){// diff here can only be in revese direction, else we pass prev check
			if(direction)
				result += cur_extremum - prev_extremum;

			prev_extremum = cur_extremum;
			cur_extremum = cur;
			direction = !direction;
		}
	}

	// Add the final ascend here
	if(direction)
		result += cur_extremum - prev_extremum;

	return result;
}

void track::filterSmooth(){
	if(m_data.size() < 2)
		return;

	float coeff_reverse = 1-g_params.smooth_coeff;

	float prev = m_data[0].ele; 
	for(int i = 1, end = m_data.size(); i< end; ++i){
		float cur = m_data[i].ele * g_params.smooth_coeff + prev * coeff_reverse;
		m_data[i].ele = cur;
		prev = cur;
	}
}
