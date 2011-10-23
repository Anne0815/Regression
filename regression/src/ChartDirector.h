#ifndef CHARTDIRECTOR_H
#define CHARTDIRECTOR_H

#include <memory>
#include "global.h"
#include "chartdir.h"

using namespace std;

class ChartDirector
{
public:
	ChartDirector(){}
	virtual ~ChartDirector(){};

	void createChart(XYChart& chart, double* xValues, double* tValues, unsigned int& number);
	void addPlot( XYChart& chart, double* xValues, double* tValues, unsigned int& number);


private:
	void addCurve(XYChart& chart, double* xValues, double* tValues, unsigned int& number);
	void addLine(XYChart& chart, double* xValues, double* tValues, unsigned int& number);
};

#endif