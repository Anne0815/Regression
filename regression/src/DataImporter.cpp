#include "DataImporter.h"
#include <QTextStream>
#include <QStringList>
#include <iostream>


void DataImporter::getDataPoints( QString& path, vector<DataPoint>& data )
{
	QFile file(path);

	if( !file.open(QIODevice::ReadOnly) )
	{
		cout << "Cannot open file!" << std::endl;
		return;
	}

	QTextStream stream(&file);
	while( !stream.atEnd() )
	{
		QString line = stream.readLine();
		QStringList list = line.split( ("\t") );
		QString first = list.at(0);
		QString second = list.at(1);

		bool ok_x, ok_y;
		float x = first.toFloat(&ok_x);
		float y = second.toFloat(&ok_y);

		if( ok_x && ok_y )
		{
			DataPoint dp(x, y);
			data.push_back(dp);
			continue;
		}

		cout << "Init new Datapoint from textline failed" << endl;
	}
}