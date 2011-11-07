#ifndef REGULARIZATION_H
#define REGULARIZATION_H

#include "global.h"

class Regularization
{
public:
	Regularization(){}
	virtual ~Regularization(){}

	double calcErms( unsigned int& m, const vector<DataPoint> datapoints, const vector<double> coefficients );
};
#endif