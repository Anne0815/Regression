#define _USE_MATH_DEFINES
#include <cmath>

#include "DataGenerator.h"



void DataGenerator::generateDataSin(unsigned int& number, vector<DataPoint>& dataPoints)
{
	for( int i = 0; i < number; ++i )
	{
		float x = (float)( i / 10.0f );
		float result = sin( (2.0 * M_PI * x) );
		DataPoint p(i, result);
		dataPoints.push_back(p);
	}
}

void DataGenerator::generateDataSinNoise(unsigned int& number, vector<DataPoint>& dataPoints)
{
	for( int i = 0; i < number; ++i )
	{
		float x = (float)( i / 10.0f );
		float noise = (float)((rand() % 100) / 100.0f);

		float result = sin( (2.0 * M_PI * x) );
		
		DataPoint p(i-noise, result+noise);
		dataPoints.push_back(p);
	}
}