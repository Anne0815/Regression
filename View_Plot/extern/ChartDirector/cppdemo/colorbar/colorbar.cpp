#include "chartdir.h"

int main(int argc, char *argv[])
{
    // The data for the bar chart
    double data[] = {85, 156, 179.5, 211, 123};

    // The labels for the bar chart
    const char *labels[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};

    // The colors for the bar chart
    int colors[] = {0xb8bc9c, 0xa0bdc4, 0x999966, 0x333366, 0xc3c3e6};

    // Create a XYChart object of size 300 x 220 pixels. Use golden background color.
    // Use a 2 pixel 3D border.
    XYChart *c = new XYChart(300, 220, Chart::goldColor(), -1, 2);

    // Add a title box using 10 point Arial Bold font. Set the background color to
    // metallic blue (9999FF) Use a 1 pixel 3D border.
    c->addTitle("Daily Network Load", "arialbd.ttf", 10)->setBackground(
        Chart::metalColor(0x9999ff), -1, 1);

    // Set the plotarea at (40, 40) and of 240 x 150 pixels in size
    c->setPlotArea(40, 40, 240, 150);

    // Add a multi-color bar chart layer using the given data and colors. Use a 1
    // pixel 3D border for the bars.
    c->addBarLayer(DoubleArray(data, sizeof(data)/sizeof(data[0])), IntArray(colors,
        sizeof(colors)/sizeof(colors[0])))->setBorderColor(-1, 1);

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));

    // Output the chart
    c->makeChart("colorbar.png");

    //free up resources
    delete c;
    return 0;
}

