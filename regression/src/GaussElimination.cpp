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

	if( row != v.size() )
	{
		cout << "Length of vector matched not matrix size." << endl;
		return vector<double>(0);
	}

	// vector als zusätzliche spalte an matrix hängen
	int newcol = col + 1;
	for(unsigned int i = 0; i < row; ++i)
	{
		matrix[i].push_back(v[i]);
	}

	// für alle reihen
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

	vector<double> coefficients(row);

	// letzte spalte = coefficients -> return letzte spalte als vector
	for(unsigned int i = 0; i < row; ++i)
		coefficients[i] = matrix[i][col];

	return coefficients;
}

vector<double> GaussElimination::solveLinearEquationByBigFloat(vector<vector<double>> matrix, vector<double> v)
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

	if( row != v.size() )
	{
		cout << "Length of vector matched not matrix size." << endl;
		return vector<double>(0);
	}

	// umwandlung in bigfloats und anhängen des vectors
	vector<vector<BigFloat>> matrixBF(row);
	unsigned int newcol = col + 1;

	for(unsigned int r = 0; r < row; ++r)
	{
		vector<BigFloat> vBF(newcol);
		matrixBF[r] = vBF;
		for(unsigned c = 0; c < newcol; ++c)
		{
			BigFloat bf;
			// letzte spalte kommt vom vector
			if( c == col )
				bf.set_with_double( v[r] );
			else
				bf.set_with_double( matrix[r][c] );

			matrixBF[r][c] = bf;
		}
	}

	//writeMatrix(matrixBF);

	// für alle reihen
	for(unsigned int indexDiagonal = 0; indexDiagonal < row; ++indexDiagonal)
	{
		bool success = handleEliminatingValuesInRowByBigFloat(matrixBF, indexDiagonal);
		if(!success)
		{
			cout << "Current row has problems. Row: " << indexDiagonal << endl;
			return vector<double>(0);
		}
	}

	// überprüfung, ob auch wirklich nur in matrix[indexDiagonal][indexDiagonal] == 1 und alles andere 0 ausser letzte spalte
	/*bool success = testCorrectnessEndformByBigFloat(matrixBF);
	
	if(!success)
	{
		cout << "Endform of matrix is not correct." << endl;
		return vector<double>(0);
	}*/

	writeMatrix(matrixBF);

	vector<double> coefficients(row);

	// letzte spalte = coefficients -> return letzte spalte als vector
	for(unsigned int i = 0; i < row; ++i)
		coefficients[i] = matrixBF[i][col].getdouble();

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

bool GaussElimination::handleEliminatingValuesInRowByBigFloat(vector<vector<BigFloat>>& matrix, int indexDiagonal)
{
	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	bool success = changeValuesInRowByBigFloat(matrix, indexDiagonal);

	/*cout << "Go to identity row number " << indexDiagonal << endl;
	cout << "Matrix[" << indexDiagonal << "][" << indexDiagonal << "] have to be unequal 0. ";
	writeMatrix(matrix);*/

	if(!success)
	{
		cout << "There is no more row for changing the values." << endl;
		return false;
	}

	// dividiere i.zeile durch zahl in i.spalte
	BigFloat value = matrix[indexDiagonal][indexDiagonal];
	for(unsigned int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
		matrix[indexDiagonal][i] /= value;

	/*cout << "Matrix[" << indexDiagonal << "][" << indexDiagonal << "] have to be 1. ";
	writeMatrix(matrix);*/

	// in i.spalte aller anderen zeilen muss 0 stehen (subtraktion eines geeigenten vielfaches der aktuellen zeile von allen anderen zeilen)
	eliminateValuesByZeroInColByBigFloat(matrix, indexDiagonal);

	/*cout << "Column number " << indexDiagonal << " must have zeros.";
	writeMatrix(matrix);*/

	return true;
}

bool GaussElimination::changeValuesInRow(vector<vector<double>>& matrix, int indexRow)
{
	if(matrix[indexRow][indexRow] != 0 ) return true;

	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	for(unsigned int rowCounter = indexRow+1; rowCounter < row; ++rowCounter)
	{
		double value = matrix[rowCounter][indexRow];
		if(value != 0.0)
		{
			// tausche reihen
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

bool GaussElimination::changeValuesInRowByBigFloat(vector<vector<BigFloat>>& matrix, int indexRow)
{
	if( matrix[indexRow][indexRow].compare( &BigFloat(0.0) ) != 0 ) return true;

	// wenn i.zeile zahl in spalte i = 0, tausche mit zeile darunter!!, wo zahl in i.spalte != 0 -> falls nicht da, gs nicht lösbar
	for(unsigned int rowCounter = indexRow+1; rowCounter < row; ++rowCounter)
	{
		BigFloat value = matrix[rowCounter][indexRow];
		if(value.compare( &BigFloat(0.0) ) != 0 )
		{
			// tausche reihen
			for(unsigned int i = 0; i <= col; ++i) //zusätzliche spalte angefügt durch vector
			{
				BigFloat currowValue = matrix[indexRow][i];
				BigFloat changeValue = matrix[rowCounter][i];
				matrix[indexRow][i] = changeValue;
				matrix[rowCounter][i] = currowValue;
			}
			return true;
		}
	}

	return false;
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
			matrix[i][j] -= multiplyer * matrix[indexCol][j];
	}
}

void GaussElimination::eliminateValuesByZeroInColByBigFloat(vector<vector<BigFloat>>& matrix, int indexCol)
{
	for(unsigned int i = 0; i < row; ++i)
	{
		// aktuelle zeile nicht
		if(i == indexCol) continue;

		// wenn in entsprechender spalte 0 steht, nicht notwendig
		if(matrix[i][indexCol].compare( &BigFloat(0.0) ) == 0 ) continue;

		BigFloat multiplyer = matrix[i][indexCol];

		//cout << "Multiplyer Row Number " << i << " = " << multiplyer.getdouble() << endl;

		for(unsigned int j = 0; j <= col; ++j) //zusätzliche spalte angefügt durch vector
		{
			//cout << "Matrix[" << i << "][" << j << "] = " << matrix[i][j].getdouble() << " (values of current row)" << endl;
			//cout << "Matrix[" << indexCol << "][" << j << "] = " << matrix[indexCol][j].getdouble() << endl;

			BigFloat temp = multiplyer * matrix[indexCol][j];
			//cout << matrix[indexCol][j].getdouble() << " * " << multiplyer.getdouble() << " = " << temp.getdouble() << endl;
			BigFloat res = matrix[i][j] - temp;
			//cout << matrix[i][j].getdouble() << " - " << temp.getdouble() << " = " << res.getdouble() << endl;
			
			matrix[i][j] = res;
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

bool GaussElimination::testCorrectnessEndformByBigFloat(vector<vector<BigFloat>>& matrix)
{
	// überprüfung, ob auch wirklich nur in matrix[indexDiagonal][indexDiagonal] == 1 und alles andere 0 ausser letzte spalte
	for(unsigned int i = 0; i < row; ++i)
	{
		if( matrix[i][i].compare( &BigFloat(1.0) ) != 0) return false;

		for(unsigned int j = 0; j < col; ++j)	// zusätzliche spalte (col+1) sollte nicht 0 sein
			if(matrix[i][j].compare( &BigFloat(0.0), 100 ) != 0 && i !=j ) 
				return false;
	}

	return true;
}

void GaussElimination::writeMatrix( vector<vector<BigFloat>>& matrixBF )
{
	cout << "Matrix:" << endl;
	for(unsigned int i = 0; i < row; ++i)
	{
		for(unsigned int j = 0; j <= col; ++j)
			cout << matrixBF[i][j].getdouble() << " ";
		cout << endl;
	}
}