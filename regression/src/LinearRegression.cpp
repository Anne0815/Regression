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
	matrix.clear();
	matrix.resize(m);

	for(unsigned int i = 0; i < m; ++i)
		matrix[i] = vector<double>(m, 0.0);

	xValues.clear();
	tValues.clear();
	xValues.resize((m*2), 0.0);
	tValues.resize(m, 0.0);

	createMatrixLinearEquationsSystem(dataPoints, m);
	return gauss.solveLinearEquationByBigFloat(matrix, tValues);
}