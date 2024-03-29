#include <cmath>
#include <iostream>
#include "LinearRegression.h"

LinearRegression::LinearRegression()
{
}

LinearRegression::~LinearRegression()
{
	
}

void LinearRegression::createLookUpTables(const vector<DataPoint>& dataPoints)
{
	DataPoint cdp;
	
	for(unsigned int n = 0; n < dataPoints.size(); ++n)
	{
		cdp = dataPoints[n];
		for(int j = 0; j < xValues.size(); ++j)
		{
			double xpowj = pow(cdp.x, j);
			xValues[j] += xpowj;

			if( j < tValues.size() )
				tValues[j] += cdp.t * xpowj; 

		}	
	}
}

void LinearRegression::createMatrixLinearEquationsSystem(const vector<DataPoint>& dataPoints, unsigned int m)
{
	createLookUpTables(dataPoints);

	for( unsigned int row = 0; row < m; ++row )
	{
		for( unsigned int column = 0; column < m; ++column )
			matrix[row][column] = xValues[row+column];
	}
}


vector<double> LinearRegression::calculateCoefficients(unsigned int m, const vector<DataPoint>& dataPoints)
{
	matrix.clear();
	matrix.resize(m);

	for(unsigned int i = 0; i < m; ++i)
		matrix[i] = vector<double>(m, 0.0);

	xValues.clear();
	tValues.clear();
	xValues.resize((m*2), 0.0);
	tValues.resize(m, 0.0);

	createMatrixLinearEquationsSystem(dataPoints, m);
	return gauss.solveLinearEquation(matrix, tValues);
}

vector<double> LinearRegression::calculateCoefficientsBigFloat(unsigned int m, const vector<DataPoint>& dataPoints)
{
	matrixBigFloat.clear();
	matrixBigFloat.resize(m);

	for(unsigned int i = 0; i < m; ++i)
		matrixBigFloat[i] = vector<BigFloat>(m, 0.0);

	xValuesBigFloat.clear();
	tValuesBigFloat.clear();
	xValuesBigFloat.resize((m*2), 0.0);
	tValuesBigFloat.resize(m, 0.0);

	createMatrixLinearEquationsSystemBigFloat(dataPoints, m);
	return gauss.solveLinearEquationByBigFloat(matrixBigFloat, tValuesBigFloat);
}

vector<double> LinearRegression::calculateCoefficientsLambda(unsigned int m, const vector<DataPoint>& dataPoints, const double lambda)
{
	matrix.clear();
	matrix.resize(m);

	for(unsigned int i = 0; i < m; ++i)
		matrix[i] = vector<double>(m, 0.0);

	xValues.clear();
	tValues.clear();
	xValues.resize((m*2), 0.0);
	tValues.resize(m, 0.0);

	createMatrixLinearEquationsSystemLambda( dataPoints, m, lambda );
	return gauss.solveLinearEquationByBigFloat(matrix, tValues);
}

vector<double> LinearRegression::calculateCoefficientsBigFloatLambda(unsigned int m, const vector<DataPoint>& dataPoints, const double lambda)
{
	matrixBigFloat.clear();
	matrixBigFloat.resize(m);

	for(unsigned int i = 0; i < m; ++i)
		matrixBigFloat[i] = vector<BigFloat>(m, 0.0);

	xValuesBigFloat.clear();
	tValuesBigFloat.clear();
	xValuesBigFloat.resize((m*2), 0.0);
	tValuesBigFloat.resize(m, 0.0);

	createMatrixLinearEquationsSystemBigFloatLambda( dataPoints, m, BigFloat(lambda) );
	return gauss.solveLinearEquationByBigFloat(matrixBigFloat, tValuesBigFloat);
}

void LinearRegression::createMatrixLinearEquationsSystemBigFloat(const vector<DataPoint>& dataPoints, unsigned int m)
{
	createLookUpTablesBigFloat(dataPoints);

	for( unsigned int row = 0; row < m; ++row )
	{
		for( unsigned int column = 0; column < m; ++column )
			matrixBigFloat[row][column] = xValuesBigFloat[row+column];
	}
}

void LinearRegression::createMatrixLinearEquationsSystemLambda(const vector<DataPoint>& dataPoints, unsigned int m, double lambda)
{
	createLookUpTables(dataPoints);

	for( unsigned int row = 0; row < m; ++row )
	{
		for( unsigned int column = 0; column < m; ++column )
		{
			matrix[row][column] = xValues[row+column];

			//cout << "lambda = " << lambda.getdouble() << endl;
			if( row == column )
				matrix[row][column] += lambda;
		}
	}
}

void LinearRegression::createMatrixLinearEquationsSystemBigFloatLambda(const vector<DataPoint>& dataPoints, unsigned int m, BigFloat lambda)
{
	createLookUpTablesBigFloat(dataPoints);

	for( unsigned int row = 0; row < m; ++row )
	{
		for( unsigned int column = 0; column < m; ++column )
		{
			matrixBigFloat[row][column] = xValuesBigFloat[row+column];

			//cout << "lambda = " << lambda.getdouble() << endl;
			if( row == column )
				matrixBigFloat[row][column] += lambda;
		}
	}
}

void LinearRegression::createLookUpTablesBigFloat(const vector<DataPoint>& dataPoints)
{
	DataPoint cdp;
	
	for(unsigned int n = 0; n < dataPoints.size(); ++n)
	{
		cdp = dataPoints[n];
		for(int j = 0; j < xValuesBigFloat.size(); ++j)
		{
			//double xpowj = pow(cdp.x, j);
			BigFloat bf;
			bf.pow( &BigFloat(cdp.x), j );

			xValuesBigFloat[j] += bf;
			//xValues[j] += xpowj;

			if( j < tValuesBigFloat.size() )
				//tValuesBigFloat[j] += cdp.t * xpowj; 
				tValuesBigFloat[j] += BigFloat(cdp.t) * bf;
		}	
	}
}
