#include <cmath>
#include "LinearRegression.h"

LinearRegression::LinearRegression()
{
	
}

LinearRegression::LinearRegression( unsigned int m, vector<DataPoint> dataPoints) : m(m), dataPoints(dataPoints)
{
	matrix = new float*[m];

	for( int i = 0; i < m; ++i )
		matrix[i] = new float[m];

	xValues.resize((m*2), 0.0f);
	tValues.resize((m*2), 0.0f);
}

void LinearRegression::createLookUpTables()
{
	DataPoint cdp;
	
	for( unsigned int n = 0; n < dataPoints.size(); ++n )
	{
		cdp = dataPoints[n];
		for( int j = 0; j < (m*2); ++j )
		{
			float xpowj = pow(cdp.x, j);
			xValues[j] += xpowj;
			tValues[j] += cdp.t * xpowj; 
		}
	}
}

void LinearRegression::createMatrixLinearEquationsSystem()
{
	for( unsigned int column = 0; column < m; ++column )
	{
		for( unsigned int row = 0; row < m; ++row )
			matrix[column][row] = xValues[row+column];
	}
}
