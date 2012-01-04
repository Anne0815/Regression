#include <QApplication>
#include <memory>
#include <cmath>
#include "global.h"
#include "QControlView.h"

#include "ChartDirector.h"
#include "QViewChart.h"
#include "DataImporter.h"
#include "DataGenerator.h"
#include "LinearRegression.h"
#include "Regularization.h"
#include "Controller.h"

#include "UnitTesting.h"

int main( int argc, char* argv[] )
{
	// app instanziieren und starten
	QApplication app( argc, argv );

	QControlView controlview;
	
	return app.exec();
}

//void datapoints2doublepointer(vector<DataPoint> datapoints, double* x, double* t)
//{
//	for( unsigned int i = 0; i < datapoints.size(); ++i )
//	{
//		x[i] = (double)(datapoints[i].x);
//		t[i] = (double)(datapoints[i].t);
//	}
//}
//
//void unittesting()
//{
//	UnitTesting ui;
//   
//	//ui.test_createLookUpTables();
//    //ui.test_createMatrixLinearEquationsSystem();
//    //ui.test_getDataPoints(filename);
//	//ui.test_determinant();
//	//ui.test_solveLinearEquationByCramerRule();
//	//ui.test_solveLinearEquationByGauss();
//	//ui.test_solveLinearEquationByGaussBigFloat();
//	ui.test_bigfloatOperatorOverloading();
//	//ui.test_solveLinearEquationByGauss();
//	//ui.test_calcErms();
//	//ui.test_detectOptimalByCalcErms();
//}
//
//void graphic( shared_ptr<QViewChart> view)
//{
//	vector<DataPoint> dataPoints;
//	unsigned int number;
//
//	// get data points from file
//	QString filename = view->openDirectory();
//	DataImporter importer;
//	importer.getDataPoints(filename, dataPoints);
//	number = dataPoints.size();
//
//	// get data points from generator
//	//DataGenerator generator;
//	//number = 10;
//	//generator.generateDataSin(number, dataPoints);
//
//	// chartdirector expected double pointer
//	double* xValues = new double[number];
//	double* tValues = new double[number];
//	datapoints2doublepointer(dataPoints, xValues, tValues);
//
//	// create and show chart
//	ChartDirector chartdir;
//	XYChart chart(1, 1);
//	chartdir.createChart(chart, "graphic");
//	chartdir.addPlot(chart, xValues, tValues, number);
//	//chartdir.createChart(chart, xValues, tValues, number);
//
//	// second data set
//	/*dataPoints.clear();
//	generator.generateDataSinNoise(number, dataPoints);
//	datapoints2doublepointer(dataPoints, xValues, tValues);
//	chartdir.addPlot(chart, xValues, tValues, number);*/
//   
//	view->setChart( &chart );
//
//	delete[] xValues, tValues;
//}
//
//// originNPoints is neccessary for keep in range with new points
//vector<DataPoint> calculateTestPointsForGraphic(vector<double> coefficients, unsigned int& nPoints, double maxX, double minX)
//{
//	vector<DataPoint> points(nPoints);
//
//	double range = maxX - minX;
//	//double ticks = range / nPoints - minX;
//	double ticks = range / nPoints;
//
//	for( unsigned int i = 0; i < nPoints; ++i )
//	{
//		DataPoint p;
//		double x = (double)(double(i) * ticks );
//		p.x = x;
//		p.t = coefficients[0];
//		for(int exp = 1; exp < coefficients.size(); ++exp ) 
//			p.t +=  coefficients[exp] * pow(x, exp);
//		points[i] = p;
//	}
//
//	return points;
//}
//
//void firstLinearRegression( shared_ptr<QViewChart> view )
//{   
//	vector<DataPoint> dataPoints;
//	unsigned int number = 10;
//
//	// get data points from generator
//	//DataGenerator generator;
//	//generator.generateDataSinNoise(number, dataPoints);
//
//	// get data points from dataimporter
//	DataImporter importer;
//	importer.getDataPoints(view->openDirectory(), dataPoints);
//
//	// chartdirector expected double pointer
//	double* xValues_10 = new double[number];
//	double* tValues_10 = new double[number];
//	datapoints2doublepointer(dataPoints, xValues_10, tValues_10);
//
//	// create chart with data points and a line between
//	ChartDirector chartdir;
//	XYChart chart(1, 1);
//	chartdir.createChart(chart, "Linear Regression", "x", "t");
//	chartdir.addPlot(chart, xValues_10, tValues_10, number);
//	//chartdir.createChart(chart, xValues_10, tValues_10, number);
//	chartdir.addLine(chart, xValues_10, tValues_10, number, 0xf0f0f0);
//
//	// calculate function by linear regression
//	LinearRegression linRegr;
//	unsigned int m = 10;
//	vector<double> coefficients = linRegr.calculateCoefficients(m, dataPoints);
//
//	if(coefficients.size() == 0) return;
//
//	// create test points calculated by function
//	unsigned int n = 50;
//	double* xValues_50 = new double[n];
//	double* tValues_50 = new double[n];
//	double maxX = dataPoints.at( dataPoints.size()-1 ).x;
//	double minX = dataPoints.at(0).x; 
//	datapoints2doublepointer( calculateTestPointsForGraphic(coefficients, n, maxX, minX), xValues_50, tValues_50);
//	//chartdir.addPlot(chart, xValues_50, tValues_50, n);
//	chartdir.addLine(chart, xValues_50, tValues_50, n, 0x009900);
//
//	view->setChart( &chart );
//
//	chart.makeChart("chart.png");
//
//	for( vector<double>::iterator b = coefficients.begin(), e = coefficients.end(); b != e; ++b )
//		cout << "coefficient: " << *b << endl;
//
//	delete[] xValues_10, tValues_10;
//	delete[] xValues_50, tValues_50;
//}
//
//void compareCoefficientsDoubleBigFloat( shared_ptr<QViewChart> view, vector<double>& originCoefficients )
//{
//	vector<DataPoint> dataPoints;
//	unsigned int number = 10;
//	unsigned int m = 10;
//
//	// get data points from dataimporter
//	DataImporter importer;
//	importer.getDataPoints(view->openDirectory(), dataPoints);
//
//	// by double
//	LinearRegression linReg;
//	vector<double> coefficientsDouble = linReg.calculateCoefficients(m, dataPoints);
//	// by bigfloat
//	vector<double> coefficientsBigFloat = linReg.calculateCoefficientsBigFloat(m, dataPoints);
//
//	cout << "origin" << '\t' << '\t' << "double" << '\t' << '\t' << "bigfloat" << endl;
//
//	for(unsigned int i = 0; i < m; ++i)
//	{
//		cout << endl;
//		cout << originCoefficients[i] << '\t' << '\t' << coefficientsDouble[i] << '\t' << '\t' << coefficientsBigFloat[i] << endl;
//		double ratioDouble = 100 - (coefficientsDouble[i] * 100 / originCoefficients[i]);
//		double ratioBigFloat = 100 - (coefficientsBigFloat[i] * 100 / originCoefficients[i]);
//		cout << 100 << '\t' << '\t' << ratioDouble << '\t' << '\t' << ratioBigFloat << endl;
//	}
//}
//
//void detectOptimalM( Controller& controller, shared_ptr<QViewChart> view, shared_ptr<QViewChart> viewFunction )
//{
//	unsigned int number = 100;
//	vector<DataPoint> datapoints(number);
//
//	// datenpunkte generieren
//	DataGenerator generator;
//	generator.generateDataSinNoise(number, datapoints);
//
//	unsigned int mMin = 1;
//	unsigned int mMax = 11;
//	// Erms für trainingpoints
//	vector<double> erms_training(mMax);
//	// Erms für testpoints
//	vector<double> erms_test(mMax);
//
//	vector<double> coefficients = controller.linearRegressionByOptimalM(datapoints, erms_training, erms_test, mMax, mMin);
//	if(coefficients.size() == 0)
//	{
//		cout << "There are no coefficients" << endl;
//		return;
//	}
//	
//	/****************************************************   drawing   *************************************************/
//	// m = waagerechte achse, erms = senkrechte achse
//	ChartDirector chartdir;
//	XYChart chartError(1, 1);
//	XYChart chartFunction(1, 1);
//
//	// error
//	double* mValues = new double[mMax];
//	double* ermsTrainingValues = new double[mMax];
//	double* ermsTestValues = new double[mMax];
//
//	for(unsigned int i = 0; i < mMax; ++i)
//	{
//		mValues[i] = i;
//		ermsTrainingValues[i] = erms_training[i];
//		ermsTestValues[i] = erms_test[i];
//	}
//
//	chartdir.createChart(chartError, "Calculating optimal M", "m", "erms");
//	chartdir.addPlot(chartError, mValues, ermsTrainingValues, mMax);
//	chartdir.addLine(chartError, mValues, ermsTrainingValues, mMax, 0x009900);
//	chartdir.addPlot(chartError, mValues, ermsTestValues, mMax); 
//	chartdir.addLine(chartError, mValues, ermsTestValues, mMax, 0x000099);
//
//	view->setChart(&chartError);
//
//	// function
//	double* xValues = new double[number];
//	double* tValues = new double[number];
//	datapoints2doublepointer(datapoints, xValues, tValues);
//
//	chartdir.createChart(chartFunction, "Linear Regression", "x", "t");
//	unsigned int i = datapoints.size();
//	chartdir.addPlot(chartFunction, xValues, tValues, i);
//
//	// minimum size of number datapoints
//	unsigned int n = 200;
//	double* xValues_50 = new double[n];
//	double* tValues_50 = new double[n];
//	double maxX = datapoints.at( datapoints.size()-1 ).x;
//	double minX = datapoints.at(0).x; 
//	datapoints2doublepointer( calculateTestPointsForGraphic(coefficients, n, maxX, minX), xValues_50, tValues_50);
//
//	chartdir.addLine(chartFunction, xValues_50, tValues_50, n, 0x009900);
//	viewFunction->setChart(&chartFunction);
//
//	delete[] mValues;
//	delete[] ermsTrainingValues;
//	delete[] ermsTestValues;
//
//	delete[] xValues;
//	delete[] tValues;
//
//	delete[] xValues_50;
//	delete[] tValues_50;
//}
//
//void lambda( Controller& controller, shared_ptr<QViewChart> view )
//{
//	// datapoints from book
//	vector<DataPoint> dataPoints;
//	unsigned int number = 10;
//	unsigned int m = 10;
//
//	// get data points from dataimporter
//	DataImporter importer;
//	importer.getDataPoints(view->openDirectory(), dataPoints);
//
//	vector<double> coefficients = controller.linearRegressionByLambda(dataPoints);
//}
//
//void fillOrigin( vector<double>& origin )
//{
//	origin.push_back(0.35);
//	origin.push_back(232.37);
//	origin.push_back(-5321.83);
//	origin.push_back(48568.31);
//	origin.push_back(-231639.30);
//	origin.push_back(640042.26);
//	origin.push_back(-1061800.52);
//	origin.push_back(1042400.18);
//	origin.push_back(-557682.99);
//	origin.push_back(125201.43);
//}
//
//
//int main(int argc, char *argv[])
//{
//	QApplication app(argc, argv);
//
//	shared_ptr<QViewChart> view = make_shared<QViewChart>();
//	shared_ptr<QViewChart> viewFunction = make_shared<QViewChart>();
//	Controller controller;
//  
//	view->show();
//	viewFunction->show();
//
//	//graphic(view);
//    //unittesting();
//
//    //firstLinearRegression(view);
//
//	//detectOptimalM(controller, view, viewFunction);
//
//	/*vector<double> origin;
//	fillOrigin(origin);
//	compareCoefficientsDoubleBigFloat(view, origin);*/
//
//	lambda(controller, view);
//   
//	return app.exec();
//}



