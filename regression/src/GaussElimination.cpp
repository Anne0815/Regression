#include "GaussElimination.h"


vector<double> GaussElimination::solveLinearEquation(vector<vector<double>> matrix, vector<double> v)
{
	row = matrix.size();
	col = matrix[0].size();

	if( row != col )
	{
		cout << "It has to be a linear equation (row != col)." << endl;
		return vector<double>(0);
	}

	if( row == 0 )
	{
		cout << "There are no member in equation (row = col = 0)." << endl;
		return vector<double>(0);
	}

	vector<double> coefficients(row);

	// vector als zusätzliche spalte an matrix hängen
	int newcol = col + 1;
	for(int i = 0; i < row; ++i)
	{
		matrix[i].resize(newcol);
		matrix[i][newcol] = v[i];
		// falls resize überschreibt, dann matrix[i].pushback(v[i])
	}

	// counter für index auf start
	int indexDiagonal = 0;

	// falls i != reihe i++ und ab 2
	for(int indexDiagonal; indexDiagonal < row; ++indexDiagonal)
	{
		bool success = handleEliminatingValuesInRow(matrix, indexDiagonal);
		if(!success)
		{
			cout << "Current row has problems. Row: " << indexDiagonal << endl;
			return vector<double>(0);
		}
	}

	// überprüfung, ob auch wirklich nur in matrix[indexDiagonal][indexDiagonal] == 1 und alles andere 0 ausser letzte spalte
	
	// letzte spalte = coefficients -> return letzte spalte als vector
	for(int i = 0; i < row; ++i)
		coefficients[i] = matrix[i][newcol];

	return coefficients;
}

bool GaussElimination::handleEliminatingValuesInRow(vector<vector<double>>& matrix, int indexDiagonal)
{
	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	bool success = changeValuesInRow(matrix, indexDiagonal);
	if(!success)
	{
		cout << "There is no more row for changing the values." << endl;
		return false;
	}

	// dividiere i.zeile durch zahl in i.spalte
	double value = matrix[indexDiagonal][indexDiagonal];
	for(int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
		matrix[indexDiagonal][i] /= value;

	// in i.spalte aller anderen zeilen muss 0 stehen (subtraktion aller zahlen einer zeile des wertes in i.spalte)
	eliminateValuesByZeroInCol(matrix, indexDiagonal);

}

bool GaussElimination::changeValuesInRow(vector<vector<double>>& matrix, int indexRow)
{
	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	if( matrix[indexRow][indexRow] == 0 )
	{
		int rowCounter = indexRow;
		int maxRowValue = row - 2;

		while( rowCounter != maxRowValue )
		{
			double value = matrix[++rowCounter][indexRow];
			if(value != 0.0)
			{
				for(int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
				{
					double currow_value = matrix[indexRow][i];
					double change_value = matrix[rowCounter][i];
					matrix[indexRow][i] = change_value;
					matrix[rowCounter][i] = currow_value;
				}

				return true;
			}
		}
	}

	return false;
}

void GaussElimination::eliminateValuesByZeroInCol(vector<vector<double>>& matrix, int indexCol)
{
	for(int i = 0; i < row; ++i)
	{
		if(i == indexCol) continue;

		double subtracter = matrix[i][indexCol];
		for(int j = 0; j <= col; ++j) //zusätzliche spalte angefügt durch vector
			matrix[i][j] -= subtracter;
	}
}