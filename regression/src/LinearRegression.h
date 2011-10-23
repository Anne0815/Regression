#ifndef LINEARREGRESSION
#define LINEARREGRESSION

#include <memory>
#include <vector>
#include "global.h"

using namespace std;

class LinearRegression{

	
public:

	LinearRegression();
	LinearRegression( unsigned int m, vector<DataPoint> dataPoints);
	virtual ~LinearRegression(){}

	// for testing
	vector<float> getXValues()							{ return xValues; }
	vector<float> getTValues()							{ return tValues; }
	float** getMatrix()									{ return matrix; }

	void createLookUpTables();
	void createMatrixLinearEquationsSystem();

private:
	
	vector<float> xValues;
	vector<float> tValues;

	vector<DataPoint> dataPoints;
	unsigned int m;
	float** matrix;

};
#endif