#include "Regularization.h"

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