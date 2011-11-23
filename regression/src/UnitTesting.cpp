#include "UnitTesting.h"
#include <iostream>

#include "LinearRegression.h" 
#include "LinearEquation.h"
#include "DataImporter.h"
#include "bigfloat.h"
#include "GaussElimination.h"

/*
erwartete Ausgabe:
xValues: 5, 12, 34, 108,...
tVlaues: 13, 33, 93, 285,...
*/
void UnitTesting::test_createLookUpTables()
{
	vector<DataPoint> dataPoints;
	dataPoints.push_back(DataPoint(2.0, 2.0));
	dataPoints.push_back(DataPoint(3.0, 4.0));
	dataPoints.push_back(DataPoint(4.0, 2.0));
	dataPoints.push_back(DataPoint(1.0, 1.0));
	dataPoints.push_back(DataPoint(2.0, 4.0));

	unsigned int m = 4;
	LinearRegression linRegr;

	linRegr.createLookUpTables(dataPoints);

	vector<double> xValues = linRegr.getXValues();
	vector<double> tValues = linRegr.getTValues();

	cout << "X_Values: " << endl;
	for(unsigned int i = 0; i < m; ++i)
		cout << xValues[i] << ", ";

	cout << endl;

	cout << "T_Values: " << endl;
	for(unsigned int i = 0; i < m; ++i)
		cout << tValues[i] << ", ";
}

/*
erwartete Ausgabe:
diagonale Matrix links unten nach rechts oben
*/
void UnitTesting::test_createMatrixLinearEquationsSystem()
{
	vector<DataPoint> dataPoints;
	int m = 4;

	dataPoints.push_back(DataPoint(2.0, 2.0));
	dataPoints.push_back(DataPoint(3.0, 4.0));
	dataPoints.push_back(DataPoint(4.0, 2.0));
	dataPoints.push_back(DataPoint(1.0, 1.0));
	dataPoints.push_back(DataPoint(2.0, 4.0));

	LinearRegression linRegr;

	linRegr.createMatrixLinearEquationsSystem(dataPoints, m);

	vector< vector<double> > matrix = linRegr.getMatrix();

	for( int c = 0; c < m; ++c )
	{
		for( int r = 0; r < m; ++r )
			cout << matrix[c][r] << " ";
		cout << endl;
	}
}

/*
Erwartete Ausgabe:
3 7
2 8
3 9
3 8
*/
void UnitTesting::test_getDataPoints(QString& path)
{
	vector<DataPoint> dataPoints;

	DataImporter importer;
	importer.getDataPoints(path, dataPoints);

	for(unsigned int i = 0; i < dataPoints.size(); ++i)
		cout << dataPoints[i].x << " " << dataPoints[i].t << endl;
}

void UnitTesting::test_determinant()
{
	vector< vector<double> > matrix3(3);
	vector<double> v1_3(3), v2_3(3), v3_3(3);
	
	LinearEquation linEqua;

	v1_3[0] = 0.0; v1_3[1] = 1.0; v1_3[2] = 2.0;
	v2_3[0] = 3.0; v2_3[1] = 2.0; v2_3[2] = 1.0;
	v3_3[0] = 1.0; v3_3[1] = 1.0; v3_3[2] = 0.0;
	matrix3[0] = v1_3;
	matrix3[1] = v2_3;
	matrix3[2] = v3_3;
	cout << "1. det(3x3 matrix) = 3 = " << linEqua.determinant(matrix3) << endl;

	v1_3[0] = -2.0; v1_3[1] = 2.0; v1_3[2] = -3.0;
	v2_3[0] = -1.0; v2_3[1] = 1.0; v2_3[2] =  3.0;
	v3_3[0] =  2.0; v3_3[1] = 0.0; v3_3[2] = -1.0;
	matrix3[0] = v1_3;
	matrix3[1] = v2_3;
	matrix3[2] = v3_3;
	cout << "2. det(3x3 matrix) = 18 = " << linEqua.determinant(matrix3) << endl;

	vector< vector<double> > matrix4(4);
	vector<double> v1_4(4), v2_4(4), v3_4(4), v4_4(4);
	v1_4[0] =  1.0; v1_4[1] = 4.0; v1_4[2] = 0.0; v1_4[3] =  3.0;
	v2_4[0] = -1.0; v2_4[1] = 2.0; v2_4[2] = 0.0; v2_4[3] =  1.0;
	v3_4[0] =  0.0; v3_4[1] = 5.0; v3_4[2] = 4.0; v3_4[3] =  2.0;
	v4_4[0] =  1.0; v4_4[1] = 0.0; v4_4[2] = 0.0; v4_4[3] = -2.0;
	matrix4[0] = v1_4;
	matrix4[1] = v2_4;
	matrix4[2] = v3_4;
	matrix4[3] = v4_4;
	cout << "4. det(4x4 matrix) = -56 = " << linEqua.determinant(matrix4) << endl;
													
}

// Das Bsp. ist von http://de.wikipedia.org/wiki/Cramersche_Regel
// 82 * x1 + 45 * x2 + 9 * x3 = 1
// 27 * x1 + 16 * x2 + 3 * x3 = 1
//  9 * x1 +  5 * x2 + 1 * x3 = 0
void UnitTesting::test_solveLinearEquationByCramerRule()
{
	vector< vector<double> > matrix3(3);
	vector<double> v1_3(3), v2_3(3), v3_3(3), vector_3(3);

	vector<double> result;

	LinearEquation linEqua;

	v1_3[0] = 82.0; v1_3[1] = 45.0; v1_3[2] = 9.0;
	v2_3[0] = 27.0; v2_3[1] = 16.0; v2_3[2] = 3.0;
	v3_3[0] =  9.0; v3_3[1] =  5.0; v3_3[2] = 1.0;
	matrix3[0] = v1_3;
	matrix3[1] = v2_3;
	matrix3[2] = v3_3;

	vector_3[0] = 1.0; vector_3[1] = 1.0; vector_3[2] = 0.0;

	result = linEqua.solveLinearEquation(matrix3, vector_3);
	cout << "11. solve linear equation(3x3 matrix) = {1, 1, -14} = " << "{" << result[0] << ", " << result[1] << ", " << result[2] << "}" << endl;


	v1_3[0] =  1.0; v1_3[1] = 0.0; v1_3[2] =  4.0;
	v2_3[0] =  1.0; v2_3[1] = 1.0; v2_3[2] =  6.0;
	v3_3[0] = -3.0; v3_3[1] = 0.0; v3_3[2] = -10.0;
	matrix3[0] = v1_3;
	matrix3[1] = v2_3;
	matrix3[2] = v3_3;

	vector_3[0] = 2.0; vector_3[1] = 3.0; vector_3[2] = 4.0;

	result = linEqua.solveLinearEquation(matrix3, vector_3);
	cout << "12. solve linear equation(3x3 matrix) = {-18, -9, 5} = " << "{" << result[0] << ", " << result[1] << ", " << result[2] << "}" << endl;
}

// Beispiel ist von Arndt Bruenner
// 0   10   0  12 =  -6
// 4   -5  -2  -8 = -17
// 0   -5   0  -4 = -23
// 4  -10   0 -16 =   2
void UnitTesting::test_solveLinearEquationByGauss()
{
	vector<vector<double>> matrix(4);
	matrix[0].push_back(0);
	matrix[0].push_back(10);
	matrix[0].push_back(0);
	matrix[0].push_back(12);

	matrix[1].push_back(4);
	matrix[1].push_back(-5);
	matrix[1].push_back(-2);
	matrix[1].push_back(-8);

	matrix[2].push_back(0);
	matrix[2].push_back(-5);
	matrix[2].push_back(0);
	matrix[2].push_back(-4);

	matrix[3].push_back(4);
	matrix[3].push_back(-10);
	matrix[3].push_back(0);
	matrix[3].push_back(-16);

	vector<double> v(4);
	v[0] = -6;
	v[1] = -17;
	v[2] = -23;
	v[3] = 2;

	GaussElimination gauss;
	vector<double> result = gauss.solveLinearEquation(matrix, v);

	cout << "solve linear equation by gauss = {-14, 15, -5, -13} = " << "{" << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << "}" << endl;
}

void UnitTesting::test_bigfloatOperatorOverloading()
{
	BigFloat a(10.0);
	BigFloat b(5.0);
	BigFloat c(20.0);
	cout << "vor allen operation: a = " << a.getdouble()  << " b = " << b.getdouble() << " c = " << c.getdouble() << endl << endl;
	
	// +
	c.add(&a, &b);
	cout << "erwartet: c.add( a , b ) = 15 = ? " << c.getdouble() << " ?" << endl;
	c.set_with_double(20.0);
	c = a + b;
	cout << "erwartet: c = a + b = 15 = ? " << c.getdouble() << " ?" << endl;
	a += b;
	cout << "erwartet: a += b = 15 = ? " << a.getdouble() << " ?" << endl;
	cout << "*****************************************************************" << endl;

	// -
	a.set_with_double(10.0);
	b.set_with_double(5.0);
	c.set_with_double(20);

	c.subtract(&a, &b);
	cout << "erwartet: c.subtract(a, b) = 5 = ? " << c.getdouble() << " ?" << endl;
	c.set_with_double(20.0);
	c = a - b;
	cout << "erwartet: c = a - b = 5 = ? " << c.getdouble() << " ?" << endl;
	a -= b;
	cout << "erwartet: a -= b = 5 = ? " << a.getdouble() << " ?" << endl;
	cout << "*****************************************************************" << endl;

	// :
	a.set_with_double(10.0);
	b.set_with_double(5.0);
	c.set_with_double(20);
	c.divide(&a, &b);
	cout << "erwartet: c.divide(a, b) = 2 = ? " << c.getdouble() << " ?" << endl;
	c.set_with_double(20);
	c = a / b;
	cout << "erwartet: c = a / b = 2 = ? " << c.getdouble() << " ?" << endl;
	a /= b;
	cout << "erwartet: a /= b = 2 = ? " << a.getdouble() << " ?" << endl;
	cout << "*****************************************************************" << endl;

	// *
	a.set_with_double(10.0);
	b.set_with_double(5.0);
	c.set_with_double(20);
	c.multiply(&a, &b);
	cout << "erwartet: c.multiply(a, b) = 50 = ? " << c.getdouble() << endl;
	c.set_with_double(20);
	c = a * b;
	cout << "erwartet: c = a * b = 50 = ? " << c.getdouble() << endl;
	a *= b;
	cout << "erwartet: a *= b = 50 = ? " << a.getdouble() << endl;
	cout << "*****************************************************************" << endl;

	BigFloat bf(a);
	cout << "a = " << a.getdouble() << endl;
	cout << "copy = " << bf.getdouble() << endl;
	a.set_with_double(111.11);
	cout << "a wird geändert: " << a.getdouble() << endl;
	cout << "copy (darf sich nicht mitverändern) = " << bf.getdouble() << endl;
}