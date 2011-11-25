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

	void createChart(XYChart& chart, const char* title, const char* xTitle = "x", const char* yTitle = "y", int width = 640, int height = 480, int color = 0xa0a0a0);
	void addPlot( XYChart& chart, double* xValues, double* yValues, unsigned int& number);

	void addCurve(XYChart& chart, double* xValues, double* yValues, unsigned int& number);
	void addLine(XYChart& chart, double* xValues, double* yValues, unsigned int& number, int color);
};

#endif