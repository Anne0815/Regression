#include <QApplication>
#include <memory>
#include <cmath>
#include "global.h"
#include "ChartDirector.h"
#include "QViewChart.h"
#include "DataImporter.h"
#include "DataGenerator.h"
#include "LinearRegression.h"

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
	ui.test_solveLinearEquationByGauss();
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
	chartdir.createChart(chart, xValues, tValues, number);

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

void firstLinearRegression( shared_ptr<QViewChart> view)
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
	chartdir.createChart(chart, xValues_10, tValues_10, number);
	chartdir.addLine(chart, xValues_10, tValues_10, number, 0xf0f0f0);

	// calculate function by linear regression
	LinearRegression linRegr;
	unsigned int m = 10;
	vector<double> coefficients = linRegr.calculateCoefficients(m, dataPoints);

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

void detectOptimalM()
{
	// 10 trainingdp, 90 testdp

	// lineare regression m = 2 - 9

	// Erms errechnen für trainingpoints
	vector<double> erms_training(9);

	// Erms errechnen für testpoints
	vector<double> erms_test(9);

	// m = waagerechte achse, erms = senkrechte achse
	ChartDirector chartdir;
	XYChart chart(1, 1);
	double* mValues = new double[9];
	for(int i = 0; i < 10; ++i)
		mValues[i] = i;

	// erms zu double[]

	delete[] mValues;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	shared_ptr<QViewChart> view = make_shared<QViewChart>();
  
	view->show();

	//graphic(view);
    unittesting();

    firstLinearRegression(view);
   
	return app.exec();
}



