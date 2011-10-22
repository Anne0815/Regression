#ifndef DATAIMPORTER
#define DATAIMPORTER

#include <QString>
#include <QFile>
#include <vector>
#include "LinearRegression.h"

using namespace std;

class DataImporter{

public:
	DataImporter(){}
	~DataImporter(){}

	typedef LinearRegression::DatePoint DatePoint;

	void getDatePoints( QString& path, vector<DatePoint>& data );

private:

	
};

#endif