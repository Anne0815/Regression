#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "global.h"
#include "Dll.h"

class DataGenerator
{
public:
	DataGenerator(){}
	~DataGenerator(){}

	DLL void generateDataSin(unsigned int& number, vector<DataPoint>& dataPoints);
	DLL void generateDataSinNoise(unsigned int& number, vector<DataPoint>& dataPoints);
};
#endif