#ifndef LINEARREGRESSION
#define LINEARREGRESSION

#include "global.h"

class LinearRegression{

public:

	LinearRegression();
	LinearRegression( unsigned int m, vector<DataPoint> dataPoints);
	virtual ~LinearRegression();

	// for testing
	vector<double> getXValues()							{ return xValues; }
	vector<double> getTValues()							{ return tValues; }
	double** getMatrix()								{ return matrix; }

	void createLookUpTables();
	void createMatrixLinearEquationsSystem();

private:
	
	vector<double> xValues;
	vector<double> tValues;

	vector<DataPoint> dataPoints;
	unsigned int m;
	double** matrix;

};
#endif