#include "Regularization.h"

#include <map>

#include "LinearRegression.h"

double Regularization::calcErms( const vector<DataPoint> datapoints, const vector<double> coefficients )
{
	DataPoint cdp;

	double erms = 0.0;

	for(unsigned int n = 0; n < datapoints.size(); ++n)
	{
		cdp = datapoints.at(n);
		double x = cdp.x;
		double functionValue = 0.0;

		// funktionsgleichung berechnen: y = w0 * xn_0 + w1 * xn_1 + w2 * xn_2 + ... + wm * xn_m
		for(int j = 0; j < coefficients.size(); ++j)
		{
			double xpowj = pow( x, j );
			functionValue += coefficients.at(j) * xpowj;	//coefficients.size() - 1 - j
		}

		// sqrt( ((y - tn) hoch 2) ) -> keine negativen fehler
		functionValue -= cdp.t;
		double curError = pow(functionValue, 2.0);
		erms += sqrt( curError );
		//erms += curError;
	}

	//erms *= 0.5;  // * 0.5 ersetzt durch: teilung durch alle n
	//erms /= datapoints.size();

	// statt fehler root-mean-square-error
	//return sqrt( erms / datapoints.size() );
	//return sqrt( erms ) / datapoints.size();
	return (erms / datapoints.size() );
}

vector<double> Regularization::detectOptimalMByLambda(const vector<DataPoint>& dataTest, const vector<DataPoint>& dataTraining, const unsigned int maxM, const int minLambda)
{
	double minError = DBL_MAX;
	vector<double> bestCoefficients;

	for(unsigned int m = 1; m < maxM; ++m)
	{
		double error;
		vector<double> coefficients = regulateByLambda(dataTest, dataTraining, m, minLambda, error);
		if(error < minError)
		{
			minError = error;
			bestCoefficients = coefficients;
		}
	}

	return bestCoefficients;
}

vector<double> Regularization::regulateByLambda(const vector<DataPoint>& dataTest, const vector<DataPoint>& dataTraining, unsigned const int m, const int minLambda, double& error)
{
	LinearRegression regression;

	vector<double> bestCoefficients(m);
	int rangeLeft = minLambda; 
	int rangeRight = 0;
	int rangeMiddle = (rangeLeft - rangeRight) / 2;

	double minError;

	const int steps = 5;
	int stepsize = abs( (rangeRight - rangeLeft) / steps );

	// for output
	//int counter = 0;

	while( stepsize > 1 )
	{
		minError = DBL_MAX;
		stepsize = abs( (rangeRight - rangeLeft) / steps );

		//cout << "stepsize: " << stepsize << endl << endl;

		for(int i = 0; i <= steps; ++i)
		{
			// right should be the highest, left the smallest value
			int t = i * stepsize;
			double curValue = rangeRight - i * stepsize;
			// handling rounding if range is not exact divided by steps
			curValue = curValue < rangeLeft ? rangeLeft : curValue;
			double lambda = exp( curValue );

			//cout << "current step: " << curValue << endl;

			// calculate coefficients and resulting error for testset for all step lambdas
			vector<double> coefficients = regression.calculateCoefficientsLambda(m, dataTraining, lambda);
			//vector<double> coefficients = regression.calculateCoefficientsBigFloatLambda(m, dataTraining, lambda);
			double error = calcErms(dataTest, coefficients);
			// find smallest error - left and right of them are new range
			if(error < minError)
			{
				minError = error;
				rangeMiddle = curValue;
				bestCoefficients = coefficients;
			}

			//cout << "resulting error: " << error << endl;
			//cout << "*****************************************************************" << endl << endl;
		}

		//cout << counter <<". run:" << endl;
		//cout << "range from " << rangeLeft << " to " << rangeRight <<": Min error was " << minError << " by " << rangeMiddle << endl;

		//cout << "Coefficients: " << endl;
		//for(int i = 0; i < bestCoefficients.size(); ++i)
		//	cout << bestCoefficients[i] << endl;

		rangeLeft = rangeMiddle - stepsize;
		rangeRight = (rangeMiddle + stepsize) > 0 ? 0 : rangeMiddle + stepsize;	// not over zero, is not necessary

		//++counter;
		//cout << endl;
	}

	cout << "m = " << m << ": error = " << error << " by lambda = " << rangeMiddle << endl << endl;

	error = minError;
	return bestCoefficients;
}