#ifndef QCONTROLVIEW_H
#define QCONTROLVIEW_H

#include <memory>
#include <set>
#include <QMainWindow>

#include "global.h"
#include "ui_ControlView.h"
#include "Controller.h"
#include "QViewChart.h"
#include "ChartDirector.h"

class QControlView : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	QControlView(QMainWindow *parent = 0);
	virtual ~QControlView(){}

private:
	QString openDirectory();

	unsigned int dialogNumber(const QString title, const int min, const int max, const int defaultValue);  
	void datapoints2doublepointer(const vector<DataPoint>& datapoints, double* x, double* t);
	vector<DataPoint> calculateTestPointsForGraphic(vector<double> coefficients, unsigned int& nPoints, double maxX, double minX);

	void paintingDatapoints(shared_ptr<QViewChart> view, XYChart& chart, const vector<DataPoint>& points);
	void paintingFunctionCurve(shared_ptr<QViewChart> view, XYChart& chart, vector<double> coefficients);

	Controller controller;
	ChartDirector chartdirector;

	vector<DataPoint> dataPoints;
	set<shared_ptr<QViewChart>> charts;

private slots:
	void openData();
	void generateData();
	void regressionSimple();
	void regressionOptimalM();
	void regressionLambda();
	void closeChart(shared_ptr<QViewChart> chart);
};

#endif