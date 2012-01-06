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
	unsigned int nPoints = dataPoints.size();
	if( !(nPoints > 0) )
	{
		cout << "There are no data points." << endl;
		return;
	}

	unsigned int m = dialogNumber("Order of regression", 1, 12, 4);
	
	// calculating coefficients
	vector<double> coefficients = controller.linearRegression(dataPoints, m);
	if(coefficients.size() == 0)
	{
		cout << "There are no coefficients" << endl;
		return;
	}

	// init member for plotting
	shared_ptr<QViewChart> viewChart = make_shared<QViewChart>();
	connect( viewChart.get(), SIGNAL( closeWindow(shared_ptr<QViewChart>) ), this, SLOT( closeChart(shared_ptr<QViewChart>) ) );
	// for saving and deleting - controlling of all chartviews
	charts.insert(viewChart);

	XYChart chart(1, 1);
	chartdirector.createChart(chart, "Linear Regression simple", "x", "t");

	// painting
	viewChart->show();
	paintingDatapoints(chart, dataPoints);
	paintingFunctionCurve(chart, coefficients);
	viewChart->setChart(&chart);

	cout << "regression simple" << endl;
}

void QControlView::regressionOptimalM()
{
	unsigned int nPoints = dataPoints.size();
	if( !(nPoints > 0) )
	{
		cout << "There are no data points." << endl;
		return;
	}

	// init objects for painting errors of training and test sets
	unsigned int mMin = 1;
	unsigned int mMax = 11;
	// Erms für trainingpoints
	vector<double> erms_training(mMax);
	// Erms für testpoints
	vector<double> erms_test(mMax);

	// calculating coefficients
	vector<double> coefficients = controller.linearRegressionByOptimalM(dataPoints, erms_training, erms_test, mMax, mMin);
	if(coefficients.size() == 0)
	{
		cout << "There are no coefficients" << endl;
		return;
	}

	// init member for plotting function
	shared_ptr<QViewChart> viewChart = make_shared<QViewChart>();
	connect( viewChart.get(), SIGNAL( closeWindow(shared_ptr<QViewChart>) ), this, SLOT( closeChart(shared_ptr<QViewChart>) ) );
	// for saving and deleting - controlling of all chartviews
	charts.insert(viewChart);

	XYChart chart(1, 1);
	chartdirector.createChart(chart, "Linear Regression By optimal M", "x", "t");

	// painting
	viewChart->show();
	paintingDatapoints(chart, dataPoints);
	paintingFunctionCurve(chart, coefficients);
	viewChart->setChart(&chart);

	// init member for plotting error curves
	shared_ptr<QViewChart> viewError = make_shared<QViewChart>();
	connect( viewError.get(), SIGNAL( closeWindow(shared_ptr<QViewChart>) ), this, SLOT( closeChart(shared_ptr<QViewChart>) ) );
	charts.insert(viewError);

	XYChart chartError(1, 1);
	chartdirector.createChart(chartError, "ERMS Training and Test", "m", "erms");

	// painting
	viewError->show();
	paintingErrorCurve(chartError, erms_training, 0x009900);
	paintingErrorCurve(chartError, erms_test, 0x000099);
	viewError->setChart(&chartError);
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

// originNPoints is neccessary for keep in range with new points
vector<DataPoint> QControlView::calculateTestPointsForGraphic(vector<double> coefficients, unsigned int& nPoints, double maxX, double minX)
{
	vector<DataPoint> points(nPoints);

	double range = maxX - minX;
	//double ticks = range / nPoints - minX;
	double ticks = range / nPoints;

	for( unsigned int i = 0; i < nPoints; ++i )
	{
		DataPoint p;
		double x = (double)(double(i) * ticks );
		p.x = x;
		p.t = coefficients[0];
		for(int exp = 1; exp < coefficients.size(); ++exp ) 
			p.t +=  coefficients[exp] * pow(x, exp);
		points[i] = p;
	}

	return points;
}

void QControlView::paintingDatapoints(XYChart& chart, const vector<DataPoint>& points)
{
	unsigned int nPoints = points.size();

	// chartdirector expected double pointer for painting in plot
	double* xValues = new double[nPoints];
	double* tValues = new double[nPoints];
	datapoints2doublepointer(dataPoints, xValues, tValues);	
	
	// painting data points
	chartdirector.addPlot(chart, xValues, tValues, nPoints);

	delete[] xValues;
	delete[] tValues;
}

void QControlView::paintingFunctionCurve(XYChart& chart, vector<double>& coefficients)
{
	// for painting curve of function it´s necessary to have many datapoints
	unsigned int n = 50;
	double* xValues = new double[n];
	double* tValues = new double[n];
	// keep in range of origin datapoints
	double maxX = dataPoints.at( dataPoints.size()-1 ).x;
	double minX = dataPoints.at(0).x; 
	datapoints2doublepointer( calculateTestPointsForGraphic(coefficients, n, maxX, minX), xValues, tValues);
	chartdirector.addLine(chart, xValues, tValues, n, 0x009900);

	delete[] xValues;
	delete[] tValues;
}

void QControlView::paintingErrorCurve(XYChart& chart, vector<double>& errors, int color)
{
	unsigned int size = errors.size();
	double* mValues = new double[size];
	double* ermsValues = new double[size];

	for(unsigned int i = 0; i < size; ++i)
	{
		mValues[i] = i;
		ermsValues[i] = errors[i];
	}

	chartdirector.addPlot(chart, mValues, ermsValues, size);
	chartdirector.addLine(chart, mValues, ermsValues, size, color);

	delete[] mValues;
	delete[] ermsValues;
}