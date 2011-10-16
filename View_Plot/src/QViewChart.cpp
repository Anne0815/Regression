#include "QViewChart.h"

QViewChart::QViewChart(QWidget *parent) : QLabel(parent)
{
	currentChart = 0;
	hotSpotTester = 0;
	currentHotSpot = -1;
}

void QViewChart::setChart(BaseChart* c)
{
    // Get the image and metrics for the chart
    QPixmap image;
    const char *chartMetrics = 0;

    if (0 != c)
    {
        // Output chart as Device Indpendent Bitmap with file headers
        MemBlock m = c->makeChart(Chart::BMP);
        image.loadFromData((uchar *)m.data, (uint)m.len);
        setFixedSize(c->getWidth(), c->getHeight());

        // Get chart metrics
        chartMetrics = c->getChartMetrics();
    }

    // Set the HBITMAP for display
    currentChart = c;
    setPixmap(image);

    // Set the chart metrics and clear the image map
    setChartMetrics(chartMetrics);
    setImageMap(0);
}

void QViewChart::setImageMap(const char *imageMap)
{
    //delete the existing ImageMapHandler
    if (0 != hotSpotTester)
        delete hotSpotTester;
    currentHotSpot = -1;

    //create a new ImageMapHandler to represent the image map
    if ((0 == imageMap) || (0 == *imageMap))
        hotSpotTester = 0;
    else
		hotSpotTester = new ImageMapHandler(imageMap);
}