#ifndef QVIEWCHART_H
#define QVIEWCHART_H

#include <memory>
#include <QLabel> 
#include "chartdir.h"

using namespace std;

class QViewChart : public QLabel, public ViewPortManager
{
	Q_OBJECT

public:
	QViewChart(QWidget *parent = 0);
	virtual ~QViewChart(){}

	virtual void setChart(BaseChart* c);
	virtual BaseChart* getChart()			{ return currentChart; }

	virtual void setImageMap(const char *imageMap);

	void closeEvent(QCloseEvent *event);

private:
	BaseChart* currentChart;          // Current BaseChart object
	ImageMapHandler* hotSpotTester;   // ImageMapHander representing the image map
	int currentHotSpot;               // The hot spot under the mouse cursor.

signals:
	void closeWindow( shared_ptr<QViewChart> chart );

};

#endif