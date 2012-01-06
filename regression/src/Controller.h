#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "global.h"
#include "Dll.h"

class Controller
{
public:
	Controller(){}
	virtual ~Controller(){}

	DLL vector<double> linearRegressionByDouble( vector<DataPoint>& datapoints, const unsigned int m );
	// simple linear regression with m as parameter
	DLL vector<double> linearRegression( vector<DataPoint>& datapoints, const unsigned int m );
	// for ronys excercise (2 < m < 9)
	DLL vector<double> linearRegressionByOptimalM( vector<DataPoint>& datapoints );
	// for variable m range
	DLL vector<double> linearRegressionByOptimalM( vector<DataPoint>& datapoints, const unsigned int mMax, const unsigned int mMin );
	// for drawing error plot
	DLL vector<double> linearRegressionByOptimalM( vector<DataPoint>& datapoints, vector<double>& ermsTraining, vector<double>& ermsTest, const unsigned int mMax, const unsigned int mMin );

	// for checking correctness of calculating with lambda (=test with bookvalues)
	DLL vector<double> linearRegressionByLambda( vector<DataPoint>& datapoints );
};

#endif