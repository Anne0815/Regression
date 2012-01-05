#ifndef QCONTROLVIEW_H
#define QCONTROLVIEW_H

#include <QMainWindow>
#include "global.h"
#include "ui_ControlView.h"
#include "DataImporter.h"
#include "DataGenerator.h"

class QControlView : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	QControlView(QMainWindow *parent = 0);
	virtual ~QControlView(){}

private:
	QString openDirectory();

	DataImporter importer;
	DataGenerator generator;

	vector<DataPoint> dataPoints;

private slots:
	void openData();
	void generateData();
	void regressionSimple();
	void regressionOptimalM();
	void regressionLambda();
};

#endif