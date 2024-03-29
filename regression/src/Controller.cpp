#include "Controller.h"
#include "LinearRegression.h"
#include "Regularization.h"

vector<double> Controller::linearRegressionByDouble( vector<DataPoint>& datapoints, const unsigned int m )
{
	LinearRegression regression;
	return regression.calculateCoefficients(m, datapoints);
}

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
	// separate training and test set of datapoints
	unsigned int ratio = 10;
	vector<DataPoint> trainingDatapoints(datapoints.size() / ratio);
	separateTrainingAndTestDatapoints(datapoints, trainingDatapoints, ratio);

	// saving results
	vector<vector<double>> coefficientsVectors(mMax);

	// optimal m, delta between errors
	unsigned int optimal_M;
	double error = DBL_MAX;

	Regularization regularization;

	// linear regression
	for( unsigned int m = mMin; m < mMax; ++m )
	{
		// calculation coeeficients by training datapoints
		vector<double> coefficients = linearRegression(trainingDatapoints, m);

		// error for both sets and saving errors and coefficients
		double ermsTr = regularization.calcErms(trainingDatapoints, coefficients);
		ermsTraining[m] = ermsTr;
		double ermsTe = regularization.calcErms(datapoints, coefficients);
		ermsTest[m] = ermsTe;
		coefficientsVectors[m - mMin] = coefficients;
		// output on console
		/*cout << "M = " << m << endl;
		cout << "ERMS Training: " << ermsTr << endl;
		cout << "ERMS Test: " << ermsTe << endl << endl;*/

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
	// separate training and test set of datapoints
	unsigned int ratio = 10;
	vector<DataPoint> trainingDatapoints(datapoints.size() / ratio);
	separateTrainingAndTestDatapoints(datapoints, trainingDatapoints, ratio);

	Regularization regularization;
	unsigned int maxM = 10;
	int minLambda = -1000;
	return regularization.detectOptimalMByLambda(datapoints,trainingDatapoints, maxM, minLambda);
}

void Controller::separateTrainingAndTestDatapoints(vector<DataPoint>& datapoints, vector<DataPoint>& trainingDatapoints, const unsigned int ratio)
{
	unsigned int nTraining = datapoints.size() / ratio;
	
	// 10% for calculating coefficients, 90% for optimization and proofing of correctness
	for(unsigned int i = 0; i < nTraining; ++i)
	{
		unsigned int index = i * ratio;
		trainingDatapoints[i] = datapoints[index];
		index = index == 0 ? 0 : index - 1;
		datapoints.erase(datapoints.begin() + index);
	}
}