#include "Regularization.h"

double Regularization::calcErms( const vector<DataPoint> datapoints, const vector<double> coefficients )
{
	DataPoint cdp;

	double erms = 0.0;

	for(unsigned int n = 0; n < datapoints.size(); ++n)
	{
		cdp = datapoints.at(n);
		double error = 0.0;

		// funktionsgleichung berechnen: y = w0 * xn_0 + w1 * xn_1 + w2 * xn_2 + ... + wm * xn_m
		for(int j = 0; j < coefficients.size(); ++j)
		{
			double xpowj = pow( cdp.x, j );
			error += coefficients.at(j) * xpowj;
		}

		// sqrt( ((y - tn) hoch 2) ) -> keine negativen fehler
		error -= cdp.t;
		erms += sqrt( pow(error, 2.0) );
	}

	//erms *= 0.5;  // * 0.5 ersetzt durch: teilung durch alle n
	erms /= datapoints.size();

	// statt fehler root-mean-square-error
	return sqrt( 2.0 * erms / datapoints.size() );
}