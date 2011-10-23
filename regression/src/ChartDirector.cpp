#include "ChartDirector.h"

void ChartDirector::createChart(XYChart& chart, double* xValues, double* tValues, unsigned int& number)
{
	chart.setSize(640, 480);
	chart.setBackground(0xa0a0a0);

	// init plot area
	chart.setPlotArea( 50, 50, 540, 360, 0xc0c0c0, -1, 0xc0c0c0, 0xffffff, -1);

	// Add a legend box with the top center point anchored at (270, 30). Use
    // horizontal layout. Use 10 pts Arial Bold Italic font. Set the background and
    // border color to Transparent.
	/*
    LegendBox *legendBox = c->addLegend(270, 30, false, "arialbi.ttf", 10);
    legendBox->setAlignment(Chart::TopCenter);
    legendBox->setBackground(Chart::v, Chart::Transparent);
	*/

    chart.addTitle("Linear Regression", "arialbi.ttf", 15);

    chart.yAxis()->setTitle("t", "arialbi.ttf", 10);
    chart.xAxis()->setTitle("x", "arialbi.ttf", 10);

    chart.yAxis()->setWidth(1);
    chart.xAxis()->setWidth(1);

    // add a scatter layer
	DoubleArray xd(xValues, number);
    DoubleArray td(tValues, number);
	chart.addScatterLayer(xd, td, "Measurement", Chart::CircleShape, 5, 0x00ff00);
}

void ChartDirector::addPlot(XYChart& chart, double* xValues, double* tValues, unsigned int& number)
{
	// add a scatter layer
	DoubleArray xd(xValues, number);
    DoubleArray td(tValues, number);
	chart.addScatterLayer(xd, td, "Measurement", Chart::CircleShape, 5, 0x000000);
}

void ChartDirector::addCurve(XYChart& chart, double* xValues, double* tValues, unsigned int& number)
{
	SplineLayer* spline = chart.addSplineLayer();
	DoubleArray xd(xValues, number);
	DoubleArray td(tValues, number);
	spline->setXData(xd);
	spline->addDataSet(td, 0xffff00, "Curve");
}

void ChartDirector::addLine(XYChart& chart, double* xValues, double* tValues, unsigned int& number, int color)
{
	LineLayer* line = chart.addLineLayer();
	DoubleArray xd(xValues, number);
	DoubleArray td(tValues, number);
	line->setXData(xd);
	line->addDataSet(td, color, "Line");
}