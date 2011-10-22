#include <QApplication>
#include "ChartDirector.h"
#include "QViewChart.h"

#include "UnitTesting.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QViewChart view;
   ChartDirector chartdir;
   view.setChart( chartdir.curve() );

   view.show();

   UnitTesting ui;
   //ui.test_createLookUpTables();
   //ui.test_createMatrixLinearEquationsSystem();
   ui.test_getDataPoints();

   return app.exec();
}


