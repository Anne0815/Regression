#include "ChartDirector.h"

void ChartDirector::createChart(XYChart& chart, const char* title, const char* xTitle, const char* yTitle, int width, int height, int color)
{
	chart.setSize(width, height);
	chart.setBackground(color);
	
	chart.setPlotArea( 50, 50, 540, 360, 0xc0c0c0, -1, 0xc0c0c0, 0xffffff, -1);

	// Add a legend box with the top center point anchored at (270, 30). Use
    // horizontal layout. Use 10 pts Arial Bold Italic font. Set the background and
    // border color to Transparent.
	/*
    LegendBox *legendBox = c->addLegend(270, 30, false, "arialbi.ttf", 10);
    legendBox->setAlignment(Chart::TopCenter);
    legendBox->setBackground(Chart::v, Chart::Transparent);
	*/

	chart.addTitle(title, "arialbi.ttf", 15);

	chart.yAxis()->setTitle(yTitle, "arialbi.ttf", 10);
    chart.xAxis()->setTitle(xTitle, "arialbi.ttf", 10);

	chart.yAxis()->setWidth(1);
    chart.xAxis()->setWidth(1);

	//chart.yAxis()->setDateScale(0.0, 1.0);
	//chart.xAxis()->setDateScale(0.0, 1.0);
}

void ChartDirector::addPlot(XYChart& chart, double* xValues, double* yValues, unsigned int& number)
{
	// add a scatter layer
	DoubleArray xd(xValues, number);
    DoubleArray td(yValues, number);
	
	chart.addScatterLayer(xd, td, "Measurement", Chart::CircleShape, 5, 0x000000);
}

void ChartDirector::addCurve(XYChart& chart, double* xValues, double* yValues, unsigned int& number)
{
	SplineLayer* spline = chart.addSplineLayer();
	DoubleArray xd(xValues, number);
	DoubleArray td(yValues, number);
	spline->setXData(xd);
	spline->addDataSet(td, 0xffff00, "Curve");
}

void ChartDirector::addLine(XYChart& chart, double* xValues, double* yValues, unsigned int& number, int color)
{
	LineLayer* line = chart.addLineLayer();
	DoubleArray xd(xValues, number);
	DoubleArray td(yValues, number);
	line->setXData(xd);
	line->addDataSet(td, color, "Line");
}