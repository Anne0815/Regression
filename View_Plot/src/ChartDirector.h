#ifndef CHARTDIRECTOR_H
#define CHARTDIRECTOR_H

#include <memory>
#include "chartdir.h"

using namespace std;

class ChartDirector
{
public:
	ChartDirector(){}
	virtual ~ChartDirector(){};

	XYChart* test();
	XYChart* splinefitting();
	XYChart* curve();
};
#endif