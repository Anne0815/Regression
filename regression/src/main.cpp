#include <QApplication>
#include "global.h"
#include "ChartDirector.h"
#include "QViewChart.h"
#include "DataImporter.h"
#include "DataGenerator.h"

#include "UnitTesting.h"

void datapoints2doublepointer(vector<DataPoint> datapoints, double* x, double* t)
{
	for( int i = 0; i < datapoints.size(); ++i )
	{
		x[i] = (double)(datapoints[i].x);
		t[i] = (double)(datapoints[i].t);
	}
}

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QViewChart view;
  
   view.show();
   
   vector<DataPoint> dataPoints;
   unsigned int number;

   // get data points from file
   //QString filename = view.openDirectory();
   //DataImporter importer;
   //importer.getDataPoints(filename, dataPoints);
   //number = dataPoints.size();

   // get data points from generator
   DataGenerator generator;
   number = 10;
   generator.generateDataSin(number, dataPoints);

   // chartdirector expected double pointer
   double* xValues = new double[number];
   double* tValues = new double[number];
   datapoints2doublepointer(dataPoints, xValues, tValues);

   // create and show chart
   ChartDirector chartdir;
   XYChart chart(1, 1);
   chartdir.createChart(chart, xValues, tValues, number);

   
   // second data set
   dataPoints.clear();
   generator.generateDataSinNoise(number, dataPoints);
   datapoints2doublepointer(dataPoints, xValues, tValues);
   chartdir.addPlot(chart, xValues, tValues, number);
   

   // testing
   //UnitTesting ui;
   //ui.test_createLookUpTables();
   //ui.test_createMatrixLinearEquationsSystem();
   //ui.test_getDataPoints(filename);

   view.setChart( &chart );

   delete[] xValues, tValues;
   return app.exec();
}



