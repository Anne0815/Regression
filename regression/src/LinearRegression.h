#ifndef LINEARREGRESSION
#define LINEARREGRESSION

#include "global.h"
#include "LinearEquation.h"
#include "GaussElimination.h"

class LinearRegression{

public:

	DLL LinearRegression();
	DLL virtual ~LinearRegression();

	DLL vector<double> calculateCoefficients(unsigned int m, const vector<DataPoint>& dataPoints);

	// for testing
	vector<double> getXValues()							{ return xValues; }
	vector<double> getTValues()							{ return tValues; }
	vector< vector<double> > getMatrix()				{ return matrix; }

	void createLookUpTables(const vector<DataPoint>& dataPoints);
	void createMatrixLinearEquationsSystem(const vector<DataPoint>& dataPoints, unsigned int m);

private:
	
	LinearEquation linEquation;
	GaussElimination gauss;

	vector<double> xValues;
	vector<double> tValues;
	vector< vector<double> > matrix;

};
#endif