#ifndef LINEARREGRESSION
#define LINEARREGRESSION

#include "global.h"
#include "CramerRule.h"
#include "GaussElimination.h"

class LinearRegression{

public:

	DLL LinearRegression();
	DLL virtual ~LinearRegression();

	DLL vector<double> calculateCoefficients(unsigned int m, const vector<DataPoint>& dataPoints);
	DLL vector<double> calculateCoefficientsBigFloat(unsigned int m, const vector<DataPoint>& dataPoints);
	DLL vector<double> calculateCoefficientsBigFloatLambda(unsigned int m, const vector<DataPoint>& dataPoints, const double lambda);
	DLL vector<double> calculateCoefficientsLambda(unsigned int m, const vector<DataPoint>& dataPoints, const double lambda);

	// for testing
	vector<double> getXValues()							{ return xValues; }
	vector<double> getTValues()							{ return tValues; }
	vector< vector<double> > getMatrix()				{ return matrix; }

	void createLookUpTables(const vector<DataPoint>& dataPoints);
	void createMatrixLinearEquationsSystem(const vector<DataPoint>& dataPoints, unsigned int m);

	void createLookUpTablesBigFloat(const vector<DataPoint>& dataPoints);
	void createMatrixLinearEquationsSystemBigFloat(const vector<DataPoint>& dataPoints, unsigned int m);
	void createMatrixLinearEquationsSystemBigFloatLambda(const vector<DataPoint>& dataPoints, unsigned int m, BigFloat lambda);
	void createMatrixLinearEquationsSystemLambda(const vector<DataPoint>& dataPoints, unsigned int m, double lambda);

private:
	
	CramerRule cramer;
	GaussElimination gauss;

	vector<double> xValues;
	vector<double> tValues;
	vector< vector<double> > matrix;

	vector<BigFloat> xValuesBigFloat;
	vector<BigFloat> tValuesBigFloat;
	vector< vector<BigFloat> > matrixBigFloat;

};
#endif