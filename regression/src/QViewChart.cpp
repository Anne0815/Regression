#include "QViewChart.h"
#include <QFont>
#include <QPalette>
#include <QBrush>
#include <QColor>

QViewChart::QViewChart(QWidget *parent) : QLabel(parent)
{
	currentChart = NULL;
	hotSpotTester = NULL;
	currentHotSpot = -1;

	this->setMinimumSize(400, 300);
}

/*
Implemented by ChartDirector Team.
*/
void QViewChart::setChart(BaseChart* c)
{
    // Get the image and metrics for the chart
    QPixmap image;
    const char *chartMetrics = NULL;

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
    setImageMap(NULL);
}

/*
Implemented by ChartDirector Team.
*/
void QViewChart::setImageMap(const char *imageMap)
{
    //delete the existing ImageMapHandler
    if (NULL != hotSpotTester)
        delete hotSpotTester;
    currentHotSpot = -1;

    //create a new ImageMapHandler to represent the image map
    if ((NULL == imageMap) || (NULL == *imageMap))
        hotSpotTester = NULL;
    else
		hotSpotTester = new ImageMapHandler(imageMap);
}

void QViewChart::closeEvent(QCloseEvent *event)
{
	shared_ptr<QViewChart> chart(this);
    closeWindow(chart);
}