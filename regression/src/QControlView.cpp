#include "QControlView.h"


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
	cout << "open data" << endl;
}

void QControlView::generateData()
{
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