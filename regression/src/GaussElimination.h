#ifndef GAUSSELIMINATION_H
#define GAUSSELIMINATION_H

#include "global.h"

class GaussElimination
{
public:
	GaussElimination(){}
	virtual ~GaussElimination(){}

	vector<double> solveLinearEquation(vector<vector<double>> matrix, vector<double> vector);

private:
	bool handleEliminatingValuesInRow(vector<vector<double>>& matrix, int indexDiagonal);
	bool changeValuesInRow(vector<vector<double>>& matrix, int indexRow);
	void eliminateValuesByZeroInCol(vector<vector<double>>& matrix, int indexCol);
	bool testCorrectnessEndform(const vector<vector<double>>& matrix);
	unsigned int row;
	unsigned int col;
};

#endif