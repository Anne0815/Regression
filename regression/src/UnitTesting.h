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
	DLL void test_solveLinearEquationByCramerRule();

	DLL void test_solveLinearEquationByGauss();

	DLL void test_bigfloatOperatorOverloading();

	DLL void test_calcErms();
	DLL void test_detectOptimalByCalcErms();

private:
};
#endif