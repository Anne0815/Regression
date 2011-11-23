#ifndef CRAMERRULE_H
#define CRAMERRULE_H

#include "global.h"

class CramerRule
{
public:
	CramerRule(){}
	~CramerRule(){}

	vector<double> solveLinearEquation( vector<vector<double>> matrix, vector<double> vector );
	double determinant(vector<vector<double>> matrix);
};

#endif