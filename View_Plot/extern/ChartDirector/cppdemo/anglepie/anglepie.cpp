#include "chartdir.h"
#include <stdio.h>

void createChart(int img, const char *filename)
{
    char buffer[256];

    // Determine the starting angle and direction based on input parameter
    int angle = 0;
    bool clockwise = true;
    if (img != 0) {
        angle = 90;
        clockwise = false;
    }

    // The data for the pie chart
    double data[] = {25, 18, 15, 12, 8, 30, 35};

    // The labels for the pie chart
    const char *labels[] = {"Labor", "Licenses", "Taxes", "Legal", "Insurance",
        "Facilities", "Production"};

    // Create a PieChart object of size 280 x 240 pixels
    PieChart *c = new PieChart(280, 240);

    // Set the center of the pie at (140, 130) and the radius to 80 pixels
    c->setPieSize(140, 130, 80);

    // Add a title to the pie to show the start angle and direction
    if (clockwise) {
        sprintf(buffer, "Start Angle = %d degrees\nDirection = Clockwise", angle);
        c->addTitle(buffer);
    } else {
        sprintf(buffer, "Start Angle = %d degrees\nDirection = AntiClockwise", angle)
            ;
        c->addTitle(buffer);
    }

    // Set the pie start angle and direction
    c->setStartAngle(angle, clockwise);

    // Draw the pie in 3D
    c->set3D();

    // Set the pie data and the pie labels
    c->setData(DoubleArray(data, sizeof(data)/sizeof(data[0])), StringArray(labels,
        sizeof(labels)/sizeof(labels[0])));

    // Explode the 1st sector (index = 0)
    c->setExplode(0);

    // Output the chart
    c->makeChart(filename);

    //free up resources
    delete c;
}

int main(int argc, char *argv[])
{
    createChart(0, "anglepie0.png");
    createChart(1, "anglepie1.png");
    return 0;
}

