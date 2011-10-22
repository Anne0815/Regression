#ifndef UNITTESTING
#define UNITTESTING

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

	DLL void test_getDataPoints();

private:
	typedef LinearRegression::DatePoint Datepoint;
};
#endif