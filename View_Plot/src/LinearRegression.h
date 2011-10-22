#ifndef LINEARREGRESSION
#define LINEARREGRESSION

#include <memory>
#include <vector>

using namespace std;

class LinearRegression{

	
public:
	struct DatePoint{
		float x;
		float t;
		DatePoint()
		{
			x = 0.0, t = 0.0;
		}
		DatePoint(float x, float t)
		{
			this->x = x;
			this->t = t;
		}
		~DatePoint(){}
	};

	LinearRegression();
	LinearRegression( unsigned int m, vector<DatePoint> datePoints);
	virtual ~LinearRegression(){}

	// for testing
	vector<float> getXValues()							{ return xValues; }
	vector<float> getTValues()							{ return tValues; }
	float** getMatrix()									{ return matrix; }

	void createLookUpTables();
	void createMatrixLinearEquationsSystem();

private:
	
	vector<float> xValues;
	vector<float> tValues;

	vector<DatePoint> datePoints;
	unsigned int m;
	float** matrix;

};
#endif