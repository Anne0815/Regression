#include "QControlView.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QObject>

#include "DataImporter.h"
#include "DataGenerator.h"
#include "ChartDirector.h"
#include "QViewChart.h"

QControlView::QControlView(QMainWindow *parent ) : QMainWindow(parent)
{
	setupUi(this);
	this->show();

	connect( actionOpen, SIGNAL( triggered() ), this, SLOT( openData() ));
	connect( actionGenerate, SIGNAL( triggered() ), this, SLOT( generateData() ));
	connect( actionSimple, SIGNAL( triggered() ), this, SLOT( regressionSimple() ));
	connect( actionOptimal_M, SIGNAL( triggered() ), this, SLOT( regressionOptimalM() ));
	connect( actionLambda, SIGNAL( triggered() ), this, SLOT( regressionLambda() ));
}

void QControlView::openData()
{
	DataImporter importer;
	importer.getDataPoints(openDirectory(), dataPoints);
	cout << "open data" << endl;
}

void QControlView::generateData()
{
	DataGenerator generator;
	unsigned int n = dialogNumber("Number Points", 0, 10000, 10);
	generator.generateDataSinNoise(n, dataPoints);
	cout << "generate data" << endl;
}

void QControlView::regressionSimple()
{
	if(!dataPoints.size() > 0)
	{
		cout << "There are no data points." << endl;
		return;
	}

	unsigned int m = dialogNumber("Order of regression", 1, 12, 4);
	unsigned int nPoints = dataPoints.size();
	vector<double> coefficients = controller.linearRegression(dataPoints, m);

	// painting
	double* xValues = new double[nPoints];
	double* tValues = new double[nPoints];
	datapoints2doublepointer(dataPoints, xValues, tValues);	// chartdirector expected double pointer

	ChartDirector chartdirector;
	XYChart chartFunction(1, 1);
	chartdirector.createChart(chartFunction, "Linear Regression simple", "x", "t");
	chartdirector.addPlot(chartFunction, xValues, tValues, nPoints);

	shared_ptr<QViewChart> viewChart = make_shared<QViewChart>();

	connect( viewChart.get(), SIGNAL( closeWindow(shared_ptr<QViewChart>) ), this, SLOT( closeChart(shared_ptr<QViewChart>) ) );

	viewChart->show();
	viewChart->setChart(&chartFunction);

	charts.insert(viewChart);

	cout << "regression simple" << endl;
}

void QControlView::regressionOptimalM()
{
	cout << "regression optimal m" << endl;
}

void QControlView::regressionLambda()
{
	cout << "regression lambda" << endl;
}

QString QControlView::openDirectory()
{
	QString qpath = QDesktopServices::storageLocation( QDesktopServices::DocumentsLocation );
	qpath = QFileDialog::getOpenFileName(0, tr("Open DataFile"), qpath, tr("Textfile (*.txt)"));
	return qpath;
}


unsigned int QControlView::dialogNumber(const QString title, const int min, const int max, const int defaultValue)
{
	QDialog dialog( this );
	dialog.setWindowTitle( title );
	QVBoxLayout boxLayout;

	QSpinBox spinbox(this);
	spinbox.setValue(defaultValue);
	spinbox.setMinimum(min);
	spinbox.setMaximum(max);
	spinbox.setMinimumWidth(160);

	QPushButton but( "OK", &dialog );
	but.setShortcut( Qt::Key_Enter );
	but.connect( &but, SIGNAL( clicked() ), &dialog, SLOT( reject() ) );

	boxLayout.addWidget( &spinbox );
	boxLayout.addWidget( &but );

	dialog.setLayout( &boxLayout );

	unsigned int v;
	int retval = dialog.exec();
	if ( retval == 0 ) {
		v = spinbox.value();
	}

	return v;
}

void QControlView::datapoints2doublepointer(const vector<DataPoint>& datapoints, double* x, double* t)
{
	for( unsigned int i = 0; i < datapoints.size(); ++i )
	{
		x[i] = datapoints[i].x;
		t[i] = datapoints[i].t;
	}
}

void QControlView::closeChart(shared_ptr<QViewChart> chart)
{
	charts.erase( charts.find(chart) );
	cout << "delete chart" << endl;
}