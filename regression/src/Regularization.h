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
};
#endif