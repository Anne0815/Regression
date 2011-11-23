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
	for(unsigned int i = 0; i < row; ++i)
	{
		//matrix[i].resize(newcol);
		//matrix[i][newcol] = v[i];
		// falls resize überschreibt, dann matrix[i].pushback(v[i])
		matrix[i].push_back(v[i]);
	}

	// counter für index auf start
	//int indexDiagonal = 0;

	// falls i != reihe i++ und ab 2
	for(unsigned int indexDiagonal = 0; indexDiagonal < row; ++indexDiagonal)
	{
		bool success = handleEliminatingValuesInRow(matrix, indexDiagonal);
		if(!success)
		{
			cout << "Current row has problems. Row: " << indexDiagonal << endl;
			return vector<double>(0);
		}
	}

	// überprüfung, ob auch wirklich nur in matrix[indexDiagonal][indexDiagonal] == 1 und alles andere 0 ausser letzte spalte
	bool success = testCorrectnessEndform(matrix);
	
	if(!success)
	{
		cout << "Endform of matrix is not correct." << endl;
		return vector<double>(0);
	}

	// letzte spalte = coefficients -> return letzte spalte als vector
	for(unsigned int i = 0; i < row; ++i)
		coefficients[i] = matrix[i][col];

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
	for(unsigned int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
		matrix[indexDiagonal][i] /= value;

	// in i.spalte aller anderen zeilen muss 0 stehen (subtraktion eines geeigenten vielfaches der aktuellen zeile von allen anderen zeilen)
	eliminateValuesByZeroInCol(matrix, indexDiagonal);

	return true;
}

bool GaussElimination::changeValuesInRow(vector<vector<double>>& matrix, int indexRow)
{
	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	if( matrix[indexRow][indexRow] == 0 )
	{
		int rowCounter = indexRow;
		int maxRowValue = row - 1;

		while( rowCounter != maxRowValue )
		{
			double value = matrix[++rowCounter][indexRow];
			if(value != 0.0)
			{
				for(unsigned int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
				{
					double currowValue = matrix[indexRow][i];
					double changeValue = matrix[rowCounter][i];
					matrix[indexRow][i] = changeValue;
					matrix[rowCounter][i] = currowValue;
				}

				return true;
			}
		}

		return false;
	}

	return true;
}

void GaussElimination::eliminateValuesByZeroInCol(vector<vector<double>>& matrix, int indexCol)
{
	for(unsigned int i = 0; i < row; ++i)
	{
		// aktuelle zeile nicht
		if(i == indexCol) continue;

		// wenn in entsprechender spalte 0 steht, nicht notwendig
		if(matrix[i][indexCol] == 0.0) continue;

		double multiplyer = matrix[i][indexCol];

		for(unsigned int j = 0; j <= col; ++j) //zusätzliche spalte angefügt durch vector
		{
			double d = matrix[i][j];
			double e = matrix[indexCol][j];
			double r = d - multiplyer * e;
			matrix[i][j] = r;
		}
	}
}

bool GaussElimination::testCorrectnessEndform(const vector<vector<double>>& matrix)
{
	// überprüfung, ob auch wirklich nur in matrix[indexDiagonal][indexDiagonal] == 1 und alles andere 0 ausser letzte spalte
	for(unsigned int i = 0; i < row; ++i)
	{
		if(matrix[i][i] != 1.0) return false;

		for(unsigned int j = 0; j < col; ++j)	// zusätzliche spalte (col+1) sollte nicht 0 sein
			if(matrix[i][j] != 0.0 && i !=j ) return false;
	}

	return true;
}