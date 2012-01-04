#ifndef QCONTROLVIEW_H
#define QCONTROLVIEW_H

#include <QMainWindow>
#include "global.h"
#include "ui_ControlView.h"

class QControlView : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	QControlView(QMainWindow *parent = 0);
	virtual ~QControlView(){}


private slots:
	void openData();
	void generateData();
	void regressionSimple();
	void regressionOptimalM();
	void regressionLambda();
};

#endif