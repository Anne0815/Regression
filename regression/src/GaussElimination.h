#ifndef GAUSSELIMINATION_H
#define GAUSSELIMINATION_H

#include "global.h"
#include "bigfloat.h"

class GaussElimination
{
public:
	GaussElimination(){}
	virtual ~GaussElimination(){}

	vector<double> solveLinearEquation(vector<vector<double>> matrix, vector<double> vector);
	vector<double> solveLinearEquationByBigFloat(vector<vector<double>> matrix, vector<double> vector);

private:
	bool handleEliminatingValuesInRow(vector<vector<double>>& matrix, int indexDiagonal);
	bool handleEliminatingValuesInRowByBigFloat(vector<vector<BigFloat>>& matrix, int indexDiagonal);
	bool changeValuesInRow(vector<vector<double>>& matrix, int indexRow);
	bool changeValuesInRowByBigFloat(vector<vector<BigFloat>>& matrix, int indexRow);
	void eliminateValuesByZeroInCol(vector<vector<double>>& matrix, int indexCol);
	void eliminateValuesByZeroInColByBigFloat(vector<vector<BigFloat>>& matrix, int indexCol);
	bool testCorrectnessEndform(const vector<vector<double>>& matrix);
	bool testCorrectnessEndformByBigFloat(vector<vector<BigFloat>>& matrix);
	unsigned int row;
	unsigned int col;

	void writeMatrix( vector<vector<BigFloat>>& matrixBF );
};

#endif