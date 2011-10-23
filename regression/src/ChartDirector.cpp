#include "ChartDirector.h"

XYChart* ChartDirector::createChart(double xValues[], double tValues[], unsigned int& number)
{
	// create a XYChart object, optionally layout properties
	XYChart *c = new XYChart(640, 480);
	c->setBackground(0xa0a0a0);

	// init plot area
	c->setPlotArea( 50, 50, 540, 360, 0xc0c0c0, -1, 0xc0c0c0, 0xffffff, -1);


	// Add a legend box with the top center point anchored at (270, 30). Use
    // horizontal layout. Use 10 pts Arial Bold Italic font. Set the background and
    // border color to Transparent.
	/*
    LegendBox *legendBox = c->addLegend(270, 30, false, "arialbi.ttf", 10);
    legendBox->setAlignment(Chart::TopCenter);
    legendBox->setBackground(Chart::v, Chart::Transparent);
	*/

    c->addTitle("Linear Regression", "arialbi.ttf", 15);

    c->yAxis()->setTitle("t", "arialbi.ttf", 10);
    c->xAxis()->setTitle("x", "arialbi.ttf", 10);

    c->yAxis()->setWidth(1);
    c->xAxis()->setWidth(1);

    // add a scatter layer
    c->addScatterLayer(DoubleArray(xValues, sizeof(xValues)/sizeof(xValues[0])),
					   DoubleArray(tValues, sizeof(tValues)/sizeof(tValues[0])), "Measurement",
					   Chart::CircleShape, 10, 0x000000);

	// Output the chart
    //c->makeChart("paramcurve.png");

    //free up resources
    return c;
}

XYChart* ChartDirector::createChart()
{
	unsigned int number = 4;

	double test_dataX[] = {3, 2, 4, 8};
    double test_dataY[] = {2, 4, 3, 6};

	// create a XYChart object, optionally layout properties
	XYChart *c = new XYChart(640, 480);
	c->setBackground(0xa0a0a0);

	// detect max values for axes
	double x_max = 0.0, y_max = 0.0;
	for(unsigned int i = 0; i < number; ++i )
	{
		if(test_dataX[i] > x_max) x_max = test_dataX[i];
		if(test_dataY[i] > y_max) y_max = test_dataY[i];
	}

	// init plot area
	c->setPlotArea( 50, 50, 540, 360, 0xc0c0c0, -1, 0xc0c0c0, 0xffffff, -1);


	// Add a legend box with the top center point anchored at (270, 30). Use
    // horizontal layout. Use 10 pts Arial Bold Italic font. Set the background and
    // border color to Transparent.
	/*
    LegendBox *legendBox = c->addLegend(270, 30, false, "arialbi.ttf", 10);
    legendBox->setAlignment(Chart::TopCenter);
    legendBox->setBackground(Chart::v, Chart::Transparent);
	*/

    c->addTitle("Linear Regression", "arialbi.ttf", 15);

    c->yAxis()->setTitle("t", "arialbi.ttf", 10);
    c->xAxis()->setTitle("x", "arialbi.ttf", 10);

    c->yAxis()->setWidth(1);
    c->xAxis()->setWidth(1);

    // Add a scatter layer using (dataX, dataY)
    c->addScatterLayer(DoubleArray(test_dataX, sizeof(test_dataX)/sizeof(test_dataX[0])),
					   DoubleArray(test_dataY, sizeof(test_dataY)/sizeof(test_dataY[0])), "Measurement",
					   Chart::CircleShape, 5, 0x000000);

	// Output the chart
    //c->makeChart("paramcurve.png");

    //free up resources
    return c;
}

XYChart* ChartDirector::test()
{
 // The data for the bar chart
    double data[] = {85, 156, 179.5, 211, 123};

    // The labels for the bar chart
    const char *labels[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};

    // Create a XYChart object of size 250 x 250 pixels
    XYChart* c = new XYChart(250, 250);

    // Set the plotarea at (30, 20) and of size 200 x 200 pixels
    c->setPlotArea(30, 20, 200, 200);

    // Add a bar chart layer using the given data
    c->addBarLayer(DoubleArray(data, sizeof(data)/sizeof(data[0])));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));

    // Output the chart
    //c->makeChart("simplebar.png");

	return c;
}

XYChart* ChartDirector::splinefitting()
{
    // Use random table to generate a random series. The random table is set to 1 col
    // x 51 rows, with 9 as the seed
    RanTable *rantable = new RanTable(9, 1, 51);

    // Set the 1st column to start from 100, with changes between rows from -5 to +5
    rantable->setCol(0, 100, -5, 5);

    // Get the 1st column of the random table as the data set
    DoubleArray data = rantable->getCol(0);

    // Create a XYChart object of size 600 x 300 pixels
    XYChart *c = new XYChart(600, 300);

    // Set the plotarea at (50, 35) and of size 500 x 240 pixels. Enable both the
    // horizontal and vertical grids by setting their colors to grey (0xc0c0c0)
    c->setPlotArea(50, 35, 500, 240)->setGridColor(0xc0c0c0, 0xc0c0c0);

    // Add a title to the chart using 18 point Times Bold Itatic font.
    c->addTitle("LOWESS Generic Curve Fitting Algorithm", "timesbi.ttf", 18);

    // Set the y axis line width to 3 pixels
    c->yAxis()->setWidth(3);

    // Add a title to the x axis using 12 pts Arial Bold Italic font
    c->xAxis()->setTitle("Server Load (TPS)", "arialbi.ttf", 12);

    // Set the x axis line width to 3 pixels
    c->xAxis()->setWidth(3);

    // Set the x axis scale from 0 - 50, with major tick every 5 units and minor tick
    // every 1 unit
    c->xAxis()->setLinearScale(0, 50, 5, 1);

    // Add a blue layer to the chart
    LineLayer *layer = c->addLineLayer();

    // Add a red (0x80ff0000) data set to the chart with square symbols
    layer->addDataSet(data, 0x80ff0000)->setDataSymbol(Chart::SquareSymbol);

    // Set the line width to 2 pixels
    layer->setLineWidth(2);

    // Use lowess for curve fitting, and plot the fitted data using a spline layer
    // with line width set to 3 pixels
    c->addSplineLayer(ArrayMath(data).lowess(), 0x0000ff)->setLineWidth(3);

    // Set zero affinity to 0 to make sure the line is displayed in the most detail
    // scale
    c->yAxis()->setAutoScale(0, 0, 0);

    //free up resources
    delete rantable;
    return c;
}

XYChart* ChartDirector::curve()
{
	// The data for the chart
    double data0[] = {32, 39, 23, 28, 41, 38, 26, 35, 29};
    double data1[] = {50, 55, 47, 34, 47, 53, 38, 40, 51};

    // The labels for the chart
    const char *labels[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};

    // Create a XYChart object of size 600 x 300 pixels, with a pale red (ffdddd)
    // background, black border, 1 pixel 3D border effect and rounded corners.
    XYChart *c = new XYChart(600, 300, 0xffdddd, 0x000000, 1);
    c->setRoundedFrame();

    // Set the plotarea at (55, 58) and of size 520 x 195 pixels, with white (ffffff)
    // background. Set horizontal and vertical grid lines to grey (cccccc).
    c->setPlotArea(55, 58, 520, 195, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);

    // Add a legend box at (55, 32) (top of the chart) with horizontal layout. Use 9
    // pts Arial Bold font. Set the background and border color to Transparent.
    c->addLegend(55, 32, false, "arialbd.ttf", 9)->setBackground(Chart::Transparent);

    // Add a title box to the chart using 15 pts Times Bold Italic font. The title is
    // in CDML and includes embedded images for highlight. The text is white (ffffff)
    // on a dark red (880000) background, with soft lighting effect from the right
    // side.
    c->addTitle(
        "<*block,valign=absmiddle*><*img=star.png*><*img=star.png*> Performance "
        "Enhancer <*img=star.png*><*img=star.png*><*/*>", "timesbi.ttf", 15, 0xffffff
        )->setBackground(0x880000, -1, Chart::softLighting(Chart::Right));

    // Add a title to the y axis
    c->yAxis()->setTitle("Energy Concentration (KJ per liter)");

    // Set the labels on the x axis
    c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));

    // Add a title to the x axis using CMDL
    c->xAxis()->setTitle(
        "<*block,valign=absmiddle*><*img=clock.png*>  Elapsed Time (hour)<*/*>");

    // Set the axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Add a spline layer to the chart
    SplineLayer *layer = c->addSplineLayer();

    // Set the default line width to 2 pixels
    layer->setLineWidth(2);

    // Add a data set to the spline layer, using blue (0000c0) as the line color,
    // with yellow (ffff00) circle symbols.
    layer->addDataSet(DoubleArray(data1, sizeof(data1)/sizeof(data1[0])), 0x0000c0,
        "Target Group")->setDataSymbol(Chart::CircleSymbol, 9, 0xffff00);

    // Add a data set to the spline layer, using brown (982810) as the line color,
    // with pink (f040f0) diamond symbols.
    layer->addDataSet(DoubleArray(data0, sizeof(data0)/sizeof(data0[0])), 0x982810,
        "Control Group")->setDataSymbol(Chart::DiamondSymbol, 11, 0xf040f0);

    // Add a custom CDML text at the bottom right of the plot area as the logo
    c->addText(575, 250,
        "<*block,valign=absmiddle*><*img=small_molecule.png*> <*block*>"
        "<*font=timesbi.ttf,size=10,color=804040*>Molecular\nEngineering<*/*>"
        )->setAlignment(Chart::BottomRight);

	return c;
}

