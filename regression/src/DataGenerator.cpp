#define _USE_MATH_DEFINES
#include <cmath>

#include "DataGenerator.h"



void DataGenerator::generateDataSin(unsigned int& number, vector<DataPoint>& dataPoints)
{
	for( int i = 0; i < number; ++i )
	{
		double x = (double)( i / 10.0 );
		double result = sin( (2.0 * M_PI * x) );
		DataPoint p(i, result);
		dataPoints.push_back(p);
	}
}

void DataGenerator::generateDataSinNoise(unsigned int& number, vector<DataPoint>& dataPoints)
{
	for( int i = 0; i < number; ++i )
	{
		double x = (double)( i / 10.0 );

		double result = sin( (2.0 * M_PI * x) );
		
		double noise_x = (double)((rand() % 100) / 500.0f);
		double noise_y = (double)((rand() % 100) / 500.0f);

		//DataPoint p(i + (noise_x+noise_y), result + (noise_y-noise_x));
		DataPoint p(i, result + (noise_y-noise_x));
		dataPoints.push_back(p);
	}
}