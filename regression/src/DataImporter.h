#ifndef DATAIMPORTER
#define DATAIMPORTER

#include <QString>
#include <QFile>
#include "global.h"
#include "Dll.h"


class DataImporter{

public:
	DataImporter(){}
	~DataImporter(){}

	DLL void getDataPoints( QString& path, vector<DataPoint>& data );

private:

	
};

#endif