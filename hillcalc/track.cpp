#include "track.h"

#include <io.h>
#include <fstream>
#include <iostream>

static char const* lineskip(char const* str){
	const char* result = strchr(str, '\n');
	return result? result+1: "";
}

#pragma warning(disable: 4996)
void track::fromGarminText(char const* file){
	//std::fstream fil;
	//fil.open(
	

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
		if(diff > 0)
			result += diff;
		prev = m_data[i].ele;
	}

	return result;
}

static const float epsilon = 3.5f;
float track::calcHills() const{
	if(m_data.size() < 2)
		return 0;

	float prev_extremum = m_data[0].ele;
	float cur_extremum = 0;
	int direction = 1;
	int i = 1, end = m_data.size();
	
	for(; i < end; ++i){
		float diff = m_data[i].ele - prev_extremum;
		if(fabs(diff) > epsilon){
			cur_extremum = m_data[i].ele;
			direction = diff
			break;
		}
	}

	for(; i < end; ++i){
	}
}
