#ifndef UNITTESTING
#define UNITTESTING

#include "global.h"
#include "Dll.h"
#include "LinearRegression.h" 
#include "DataImporter.h"

class UnitTesting
{
public:
	UnitTesting(){}
	~UnitTesting(){}

	DLL void test_createLookUpTables();
	DLL void test_createMatrixLinearEquationsSystem();

	DLL void test_getDataPoints(QString& path);

private:
};
#endif