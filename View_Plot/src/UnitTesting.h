#ifndef UNITTESTING
#define UNITTESTING

#include "LinearRegression.h"

class UnitTesting
{
public:
	UnitTesting(){}
	~UnitTesting(){}

	void test_createLookUpTables();
	void test_createMatrixLinearEquationsSystem();

private:
	typedef LinearRegression::DatePoint Datepoint;
};
#endif