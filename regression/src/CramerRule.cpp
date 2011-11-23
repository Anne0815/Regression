#include <iostream>
#include <cmath>
#include "CramerRule.h"

vector<double> CramerRule::solveLinearEquation(vector<vector<double>> matrix, vector<double> vector)
{
	// One of the things to check.
	if (matrix.size() == 0)
	{
		cout << "The Matrix has no elements." << endl;
		return std::vector<double>(0);
	}

    // The Dimension of the matrix.
    unsigned int rows = matrix.size();
	unsigned int cols = matrix[0].size();
            
    // It has to be a square matrix.
    if (rows != cols || rows == 0 && cols == 0)
		{
		cout << "The matrix has to be squared." << endl;
		return std::vector<double>(0);
	}

    // And the vector has to be of the length.
    if (vector.size() != rows)
	{
		cout << "The vector has to have as many rows as the matrix." << endl;
		return std::vector<double>(0);
	}

    std::vector<double> solution(rows);
    double determinante = determinant(matrix);

    // If the determinant is zero, there is no linear solution for that equation.
    if (determinante == 0) return std::vector<double>(0);

    // Apply Cramer's Rule to solve the equation.
    for (unsigned int col = 0; col < cols; ++col)
    {
		std::vector<std::vector<double>> m = matrix;
        for (unsigned int row = 0; row < rows; ++row)
        {
            m[row][col] = vector[row];
        }

        // Use the index of the column as accessor to the current row.
        // That can be done, because its a squared matrix.
        solution[col] = determinant(m)/determinante;
    }

    return solution;
}

double CramerRule::determinant(vector<vector<double>> matrix)
{
    // One of the things to check.
	if (matrix.size() == 0)
	{
		cout << "The Matrix has no elements." << endl;
		return 0;
	}

    // The Dimension of the matrix.
    unsigned int rows = matrix.size();
	unsigned int cols = matrix[0].size();
            
    // It has to be a square matrix.
    if (rows != cols || rows == 0 && cols == 0)
		{
		cout << "The matrix has to be squared." << endl;
		return 0;
	}


    // It must be bigger than that.
    if (rows == 1 && cols == 1)
		return matrix[0][0];

    // Base case of recursion is a square matrix of 2x2. Calculate its determinant.
    if (rows == 2 && cols == 2)
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

    // Use cofactors expension to calculate the determinant.
    double cofactor = 0.0;
    for (int col = 0; col < cols; col++)
    {                
        vector< vector<double> > subMatrix(rows-1);
		
        for (int y = 1; y < rows; y++)
        {
			vector<double> v(cols-1);
			subMatrix[y-1] = v;
            unsigned int index = 0;
            for (unsigned int x = 0; x < cols; x++)
            {
                if (x == col) continue;
                subMatrix[y - 1][index++] = matrix[y][x];
            }                    
        }

		cofactor += (pow(-1.0, col) * matrix[0][col] * determinant(subMatrix));
    }

    return cofactor;
}