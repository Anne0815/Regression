#ifndef UNITTESTING
#define UNITTESTING

#include <QString>
#include "global.h"
#include "Dll.h"

class UnitTesting
{
public:
	UnitTesting(){}
	~UnitTesting(){}

	DLL void test_createLookUpTables();
	DLL void test_createMatrixLinearEquationsSystem();

	DLL void test_getDataPoints(QString& path);

	DLL void test_determinant();
	DLL void test_solveLinearEquation();

	DLL void test_bigfloatOperator();

private:
};
#endif