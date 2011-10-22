#ifndef UNITTESTING
#define UNITTESTING

#include "Dll.h"
#include "LinearRegression.h" 

class UnitTesting
{
public:
	UnitTesting(){}
	~UnitTesting(){}

	DLL void test_createLookUpTables();
	DLL void test_createMatrixLinearEquationsSystem();

private:
	typedef LinearRegression::DatePoint Datepoint;
};
#endif