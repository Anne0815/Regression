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
	QFont font;
	font.setPointSize(20);
	font.setBold(true);
	this->setFont(font);

	QPalette palette;
	QBrush brush(QColor(255, 255, 255, 255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
	palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
	this->setPalette(palette);
	
	this->setStyleSheet("background-color: grey");
	this->setText(QString("Please choose a file for importing data!"));
}

//QString QViewChart::openDirectory()
//{
//	QString qpath = QDesktopServices::storageLocation( QDesktopServices::DocumentsLocation );
//	qpath = QFileDialog::getOpenFileName(0, tr("Open DataFile"), qpath, tr("Textfile (*.txt)"));
//	return qpath;
//}

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