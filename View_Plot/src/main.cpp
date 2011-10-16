#include <QApplication>
#include "ChartDirector.h"
#include "QViewChart.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QViewChart view;
   ChartDirector chartdir;
   view.setChart( chartdir.curve() );

   view.show();

   return app.exec();
}
