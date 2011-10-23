#ifndef LINEAREQUATION_H
#define LINEAREQUATION_H

#include "global.h"

class LinearEquation
{
public:
	LinearEquation(){}
	~LinearEquation(){}

	vector<double> solveLinearEquation( vector<vector<double>> matrix, vector<double> vector );
	double determinant(vector<vector<double>> matrix);
};

#endif