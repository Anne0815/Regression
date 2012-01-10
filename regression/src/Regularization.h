#ifndef REGULARIZATION_H
#define REGULARIZATION_H

#include "global.h"
#include "Dll.h"

class Regularization
{
public:
	Regularization(){}
	virtual ~Regularization(){}

	DLL double calcErms( const vector<DataPoint> datapoints, const vector<double> coefficients );

	vector<double> detectOptimalMByLambda(const vector<DataPoint>& dataTest, const vector<DataPoint>& dataTraining, const unsigned int maxM, const int minLambda);
	DLL vector<double> regulateByLambda(const vector<DataPoint>& dataTest, const vector<DataPoint>& dataTraining, unsigned const int m, const int minLambda, double& error);
};
#endif