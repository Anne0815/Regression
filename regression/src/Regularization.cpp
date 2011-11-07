#include "Regularization.h"

double Regularization::calcErms( unsigned int& m, const vector<DataPoint> datapoints, const vector<double> coefficients )
{
	DataPoint cdp;

	double erms = 0.0;

	for(unsigned int n = 0; n < datapoints.size(); ++n)
	{
		cdp = datapoints.at(n);
		double error = 0.0;

		for(int j = 0; j < coefficients.size(); ++j)
		{
			double xpowj = pow( cdp.x, j );
			error += coefficients.at(j) * xpowj;
		}

		error -= cdp.t;
		erms += pow(error, 2.0);
	}

	erms *= 0.5;

	return sqrt( 2.0 * erms / datapoints.size() );
}