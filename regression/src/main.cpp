#include <QApplication>
#include <memory>
#include <cmath>
#include "global.h"
#include "ChartDirector.h"
#include "QViewChart.h"
#include "DataImporter.h"
#include "DataGenerator.h"
#include "LinearRegression.h"
#include "Regularization.h"

#include "UnitTesting.h"

void datapoints2doublepointer(vector<DataPoint> datapoints, double* x, double* t)
{
	for( unsigned int i = 0; i < datapoints.size(); ++i )
	{
		x[i] = (double)(datapoints[i].x);
		t[i] = (double)(datapoints[i].t);
	}
}

void unittesting()
{
	UnitTesting ui;
   
	//ui.test_createLookUpTables();
    //ui.test_createMatrixLinearEquationsSystem();
    //ui.test_getDataPoints(filename);
	//ui.test_determinant();
	//ui.test_solveLinearEquation();
	//ui.test_bigfloatOperator();
	//ui.test_solveLinearEquationByGauss();
	//ui.test_calcErms();
	ui.test_detectOptimalByCalcErms();
}

void graphic( shared_ptr<QViewChart> view)
{
	vector<DataPoint> dataPoints;
	unsigned int number;

	// get data points from file
	QString filename = view->openDirectory();
	DataImporter importer;
	importer.getDataPoints(filename, dataPoints);
	number = dataPoints.size();

	// get data points from generator
	//DataGenerator generator;
	//number = 10;
	//generator.generateDataSin(number, dataPoints);

	// chartdirector expected double pointer
	double* xValues = new double[number];
	double* tValues = new double[number];
	datapoints2doublepointer(dataPoints, xValues, tValues);

	// create and show chart
	ChartDirector chartdir;
	XYChart chart(1, 1);
	chartdir.createChart(chart, "graphic");
	chartdir.addPlot(chart, xValues, tValues, number);
	//chartdir.createChart(chart, xValues, tValues, number);

	// second data set
	/*dataPoints.clear();
	generator.generateDataSinNoise(number, dataPoints);
	datapoints2doublepointer(dataPoints, xValues, tValues);
	chartdir.addPlot(chart, xValues, tValues, number);*/
   
	view->setChart( &chart );

	delete[] xValues, tValues;
}

vector<DataPoint> calculateTestPointsForGraphic(vector<double> coefficients, unsigned int& nPoints, unsigned int& originNPoints)
{
	vector<DataPoint> points(nPoints);

	for( unsigned int i = 0; i < nPoints; ++i )
	{
		DataPoint p;
		double x = (double)(double(i * originNPoints) / (double)nPoints);
		p.x = x;
		p.t = coefficients[0];
		for(int exp = 1; exp < coefficients.size(); ++exp ) 
			p.t +=  coefficients[exp] * pow(x, exp);
		points[i] = p;
	}

	return points;
}

void firstLinearRegression( shared_ptr<QViewChart> view )
{   
	vector<DataPoint> dataPoints;
	unsigned int number = 10;

	// get data points from generator
	//DataGenerator generator;
	//generator.generateDataSinNoise(number, dataPoints);

	// get data points from dataimporter
	DataImporter importer;
	importer.getDataPoints(view->openDirectory(), dataPoints);

	// chartdirector expected double pointer
	double* xValues_10 = new double[number];
	double* tValues_10 = new double[number];
	datapoints2doublepointer(dataPoints, xValues_10, tValues_10);

	// create chart with data points and a line between
	ChartDirector chartdir;
	XYChart chart(1, 1);
	chartdir.createChart(chart, "Linear Regression", "x", "t");
	chartdir.addPlot(chart, xValues_10, tValues_10, number);
	//chartdir.createChart(chart, xValues_10, tValues_10, number);
	chartdir.addLine(chart, xValues_10, tValues_10, number, 0xf0f0f0);

	// calculate function by linear regression
	LinearRegression linRegr;
	unsigned int m = 10;
	vector<double> coefficients = linRegr.calculateCoefficients(m, dataPoints);

	if(coefficients.size() == 0) return;

	// create test points calculated by function
	unsigned int n = 50;
	double* xValues_50 = new double[n];
	double* tValues_50 = new double[n];
	datapoints2doublepointer( calculateTestPointsForGraphic(coefficients, n, number), xValues_50, tValues_50);
	//chartdir.addPlot(chart, xValues_50, tValues_50, n);
	chartdir.addLine(chart, xValues_50, tValues_50, n, 0x009900);

	view->setChart( &chart );

	chart.makeChart("chart.png");

	for( vector<double>::iterator b = coefficients.begin(), e = coefficients.end(); b != e; ++b )
		cout << "coefficient: " << *b << endl;

	delete[] xValues_10, tValues_10;
	delete[] xValues_50, tValues_50;
}

void detectOptimalM( shared_ptr<QViewChart> view )
{
	// 10 trainingdp, 90 testdp = 100 datapoints
	vector<DataPoint> datapoints(100);
	vector<DataPoint> trainingDatapoints(10);
	unsigned int number = 100;
	unsigned int mMax = 11;

	// Erms für trainingpoints
	vector<double> erms_training(mMax);
	// Erms für testpoints
	vector<double> erms_test(mMax);
	// lineare regression, fehler berechner
	LinearRegression regression;
	Regularization regularization;

	// datenpunkte generieren
	DataGenerator generator;
	generator.generateDataSinNoise(number, datapoints);

	// aufteilen in 10 für training und 90 zum testen
	for(unsigned int i = 0; i < trainingDatapoints.size(); ++i)
	{
		unsigned int index = i * 10;
		trainingDatapoints[i] = datapoints[index];
		index = index == 0 ? 0 : index -1;
		datapoints.erase(datapoints.begin() + index);
	}

	// lineare regression
	for( unsigned int m = 1; m < mMax; ++m )
	{
		// koeffizienten berechnen anhand von training datapoints
		vector<double> coefficients = regression.calculateCoefficients(m, trainingDatapoints);
		// fehler berechnen für trainingset und testset
		double ermsTr = regularization.calcErms(trainingDatapoints, coefficients);
		erms_training[m] = ermsTr;
		cout << "M = " << m << endl;
		cout << "ERMS Training: " << ermsTr << endl;

		double ermsTe = regularization.calcErms(datapoints, coefficients);
		erms_test[m] = ermsTe;
		cout << "ERMS Test: " << ermsTe << endl << endl;
	}

	// m = waagerechte achse, erms = senkrechte achse
	ChartDirector chartdir;
	XYChart chart(1, 1);

	double* mValues = new double[mMax];
	double* ermsTrainingValues = new double[mMax];
	double* ermsTestValues = new double[mMax];

	for(unsigned int i = 0; i < mMax; ++i)
	{
		mValues[i] = i;
		ermsTrainingValues[i] = erms_training[i];
		ermsTestValues[i] = erms_test[i];
	}

	//chartdir.createChart(chart, mValues, ermsTrainingValues, mMax);
	chartdir.createChart(chart, "Calculating optimal M", "m", "erms");
	chartdir.addPlot(chart, mValues, ermsTrainingValues, mMax);
	chartdir.addLine(chart, mValues, ermsTrainingValues, mMax, 0x009900);
	chartdir.addPlot(chart, mValues, ermsTestValues, mMax); 
	chartdir.addLine(chart, mValues, ermsTestValues, mMax, 0x000099);

	view->setChart(&chart);

	delete[] mValues;
	delete[] ermsTrainingValues;
	delete[] ermsTestValues;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	shared_ptr<QViewChart> view = make_shared<QViewChart>();
  
	view->show();

	//graphic(view);
    //unittesting();

    //firstLinearRegression(view);

	detectOptimalM(view);
   
	return app.exec();
}



