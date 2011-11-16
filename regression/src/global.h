#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <iostream>
#include "Dll.h"

using namespace std;

struct DataPoint{
		double x;
		double t;
		DataPoint()
		{
			x = 0.0, t = 0.0;
		}
		DataPoint(double x, double t)
		{
			this->x = x;
			this->t = t;
		}
		~DataPoint(){}
	};

/*
void datapoints2floatpointer(vector<DataPoint> datapoints, double* x, double* t)
{
	for( unsigned int i = 0; i < datapoints.size(); ++i )
	{
		x[i] = datapoints[i].x;
		t[i] = datapoints[i].t;
	}
}
*/

/*

void datapoints2doublepointer(vector<DataPoint> datapoints, double* x, double* t)
{
	for( int i = 0; i < datapoints.size(); ++i )
	{
		x[i] = (double)(datapoints[i].x);
		t[i] = (double)(datapoints[i].t);
	}
}
*/

#endif