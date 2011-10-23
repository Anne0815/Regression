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

		float result = sin( (2.0 * M_PI * x) );
		
		float noise_x = (float)((rand() % 100) / 500.0f);
		float noise_y = (float)((rand() % 100) / 500.0f);

		DataPoint p(i + (noise_x+noise_y), result + (noise_y-noise_x));
		dataPoints.push_back(p);
	}
}