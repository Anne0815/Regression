#include "Controller.h"
#include "LinearRegression.h"
#include "Regularization.h"

vector<double> Controller::linearRegression( vector<DataPoint>& datapoints, const unsigned int m )
{
	LinearRegression regression;
	return regression.calculateCoefficientsBigFloat(m, datapoints);
}

vector<double> Controller::linearRegressionByOptimalM( vector<DataPoint>& datapoints )
{
	// 3 - 10 coefficients
	unsigned int mMin = 3;
	unsigned int mMax = 10;

	return linearRegressionByOptimalM(datapoints, mMax, mMin);
}

vector<double> Controller::linearRegressionByOptimalM( vector<DataPoint>& datapoints, const unsigned int mMax, const unsigned int mMin )
{
	// Erms for trainingpoints
	vector<double> ermsTraining(mMax);
	// Erms for testpoints
	vector<double> ermsTest(mMax);

	return linearRegressionByOptimalM(datapoints, ermsTraining, ermsTest, mMax, mMin);
}

vector<double> Controller::linearRegressionByOptimalM( vector<DataPoint>& datapoints, vector<double>& ermsTraining, vector<double>& ermsTest, const unsigned int mMax, const unsigned int mMin )
{
	unsigned int number = datapoints.size();
	// ca 10%
	unsigned int ratio = 10;
	vector<DataPoint> trainingDatapoints(number / ratio);
	// saving results
	vector<vector<double>> coefficientsVectors(mMax);

	// linear regression, optimization
	//LinearRegression regression;
	Regularization regularization;

	// optimal m, delta between errors
	unsigned int optimal_M;
	double error = DBL_MAX;

	// 10% for calculating coefficients, 90% for optimization
	for(unsigned int i = 0; i < trainingDatapoints.size(); ++i)
	{
		unsigned int index = i * ratio;
		trainingDatapoints[i] = datapoints[index];
		index = index == 0 ? 0 : index -1;
		datapoints.erase(datapoints.begin() + index);
	}

	// linear regression
	for( unsigned int m = mMin; m < mMax; ++m )
	{
		// calculation coeeficients by training datapoints
		vector<double> coefficients = linearRegression(trainingDatapoints, m); //regression.calculateCoefficients(m, trainingDatapoints);
		// error for both sets and saving errors and coefficients
		double ermsTr = regularization.calcErms(trainingDatapoints, coefficients);
		ermsTraining[m] = ermsTr;
		double ermsTe = regularization.calcErms(datapoints, coefficients);
		ermsTest[m] = ermsTe;
		coefficientsVectors[m - mMin] = coefficients;
		// output on console
		cout << "M = " << m << endl;
		cout << "ERMS Training: " << ermsTr << endl;
		cout << "ERMS Test: " << ermsTe << endl << endl;

		// optimal m results from smallest error of testset
		if( ermsTe < error )
		{
			optimal_M = m;
			error = ermsTe;
		}
	}

	cout << "optimal m = " << optimal_M << endl;
	return coefficientsVectors[optimal_M - mMin];
}

vector<double> Controller::linearRegressionByLambda(vector<DataPoint>& datapoints)
{
	LinearRegression linReg;

	double lambda_1 = -18.0;
	double lambda_2 = log(18.0);
	
	double lambda_3 = exp(-18.0);
	double lambda_4 = exp( lambda_2 );

	/*vector<double> c_1 = linReg.calculateCoefficientsBigFloatLambda(10, datapoints, lambda_1);
	vector<double> c_2 = linReg.calculateCoefficientsBigFloatLambda(10, datapoints, lambda_2);*/
	vector<double> c_3 = linReg.calculateCoefficientsBigFloatLambda(10, datapoints, lambda_3);
	//vector<double> c_4 = linReg.calculateCoefficientsBigFloatLambda(10, datapoints, lambda_4);

	//cout << "-18" << '\t' << "log(-18.0)" << '\t' << "exp(-18)" << '\t' << "exp( log(-18) )" << endl << endl;
	for(int i = 0; i < 10; ++i)
	{
		//cout << c_1[i] << '\t' << c_3[i] << endl;
		cout << c_3[i] << endl;
	}

	return vector<double>(0);
}