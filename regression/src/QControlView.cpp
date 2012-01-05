#include "QControlView.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>

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
	importer.getDataPoints(openDirectory(), dataPoints);
	cout << "open data" << endl;
}

void QControlView::generateData()
{
	QDialog dialog( this );
	dialog.setWindowTitle( "Number Points" );
	QVBoxLayout boxLayout;

	QSpinBox spinbox(this);
	spinbox.setValue(10);
	spinbox.setMinimum(0);
	spinbox.setMaximum(10000);
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

	generator.generateDataSinNoise(v, dataPoints);
	cout << "generate data" << endl;
}

void QControlView::regressionSimple()
{
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