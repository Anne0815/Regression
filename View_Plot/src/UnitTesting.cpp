#include "UnitTesting.h"
#include <iostream>

/*
erwartete Ausgabe:
xValues: 5, 12, 34, 108,...
tVlaues: 13, 33, 93, 285,...
*/
void UnitTesting::test_createLookUpTables()
{
	vector<Datepoint> datePoints;
	datePoints.push_back(Datepoint(2.0, 2.0));
	datePoints.push_back(Datepoint(3.0, 4.0));
	datePoints.push_back(Datepoint(4.0, 2.0));
	datePoints.push_back(Datepoint(1.0, 1.0));
	datePoints.push_back(Datepoint(2.0, 4.0));

	unsigned int m = 4;
	LinearRegression linRegr(m, datePoints);

	linRegr.createLookUpTables();

	vector<float> xValues = linRegr.getXValues();
	vector<float> tValues = linRegr.getTValues();

	cout << "X_Values: " << endl;
	for(unsigned int i = 0; i < m; ++i)
		cout << xValues[i] << ", ";

	cout << endl;

	cout << "T_Values: " << endl;
	for(int i = 0; i < m; ++i)
		cout << tValues[i] << ", ";
}

/*
erwartete Ausgabe:
diagonale Matrix links unten nach rechts oben
*/
void UnitTesting::test_createMatrixLinearEquationsSystem()
{
	vector<Datepoint> datePoints;
	int m = 4;

	datePoints.push_back(Datepoint(2.0, 2.0));
	datePoints.push_back(Datepoint(3.0, 4.0));
	datePoints.push_back(Datepoint(4.0, 2.0));
	datePoints.push_back(Datepoint(1.0, 1.0));
	datePoints.push_back(Datepoint(2.0, 4.0));

	LinearRegression linRegr(m, datePoints);

	linRegr.createLookUpTables();
	linRegr.createMatrixLinearEquationsSystem();

	float** matrix = linRegr.getMatrix();

	for( int c = 0; c < m; ++c )
	{
		for( int r = 0; r < m; ++r )
			cout << matrix[c][r] << " ";
		cout << endl;
	}
}