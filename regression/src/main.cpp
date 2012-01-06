#include <QApplication>
#include <cmath>

#include "global.h"
#include "QControlView.h"
#include "Controller.h"
#include "DataImporter.h"
#include "UnitTesting.h"

void unittesting()
{
	UnitTesting ui;
   
	//ui.test_createLookUpTables();
    //ui.test_createMatrixLinearEquationsSystem();
    //ui.test_getDataPoints(filename);
	//ui.test_determinant();
	//ui.test_solveLinearEquationByCramerRule();
	//ui.test_solveLinearEquationByGauss();
	//ui.test_solveLinearEquationByGaussBigFloat();
	//ui.test_bigfloatOperatorOverloading();
	//ui.test_solveLinearEquationByGauss();
	ui.test_calcErms();
	//ui.test_detectOptimalByCalcErms();
}


void compareCoefficientsDoubleBigFloat( Controller& controller, QControlView& view, vector<double>& originCoefficients )
{
	vector<DataPoint> dataPoints;
	unsigned int number = 10;
	unsigned int m = 10;

	// get data points from dataimporter
	DataImporter importer;
	importer.getDataPoints(view.openDirectory(), dataPoints);

	// by double
	vector<double> coefficientsDouble = controller.linearRegressionByDouble(dataPoints, m);
	// by bigfloat
	vector<double> coefficientsBigFloat = controller.linearRegression(dataPoints, m);

	cout << "origin" << '\t' << '\t' << "double" << '\t' << '\t' << "bigfloat" << endl;

	for(unsigned int i = 0; i < m; ++i)
	{
		cout << endl;
		cout << originCoefficients[i] << '\t' << '\t' << coefficientsDouble[i] << '\t' << '\t' << coefficientsBigFloat[i] << endl;
		double ratioDouble = 100 - (coefficientsDouble[i] * 100 / originCoefficients[i]);
		double ratioBigFloat = 100 - (coefficientsBigFloat[i] * 100 / originCoefficients[i]);
		cout << 100 << '\t' << '\t' << ratioDouble << '\t' << '\t' << ratioBigFloat << endl;
	}
}


void lambda(Controller& controller, QControlView& view)
{
	// datapoints from book
	vector<DataPoint> dataPoints;
	unsigned int number = 10;
	unsigned int m = 10;

	// get data points from dataimporter
	DataImporter importer;
	importer.getDataPoints(view.openDirectory(), dataPoints);

	vector<double> coefficients = controller.linearRegressionByLambda(dataPoints);
}

void fillOrigin( vector<double>& origin )
{
	origin.push_back(0.35);
	origin.push_back(232.37);
	origin.push_back(-5321.83);
	origin.push_back(48568.31);
	origin.push_back(-231639.30);
	origin.push_back(640042.26);
	origin.push_back(-1061800.52);
	origin.push_back(1042400.18);
	origin.push_back(-557682.99);
	origin.push_back(125201.43);
}

int main( int argc, char* argv[] )
{
	// controlling over view
	QApplication app( argc, argv );
	QControlView controlview;
	
	// testing
	unittesting();

	Controller controller;

	// first attempt
	//lambda(controller, controlview);

	//// comparing calculating big number vs simple double
	//vector<double> origin;
	//fillOrigin(origin);
	//compareCoefficientsDoubleBigFloat(controller, controlview, origin);

	return app.exec();
}