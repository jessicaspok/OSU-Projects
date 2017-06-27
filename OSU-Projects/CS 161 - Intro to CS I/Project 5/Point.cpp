/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 23, 2015
** Description: This is the implementation of Point member functions
***************************************************************************/

#include <cmath>
#include "Point.hpp"

// default constructor
Point::Point()
{
	setXCoord(0);
	setYCoord(0);
}

// constructor
Point::Point(double xVal, double yVal)
{
	setXCoord(xVal);
	setYCoord(yVal);
}

// Point::setXCoord sets the value of the member variable XCoord
void Point::setXCoord(double xVal)
{
	XCoord = xVal;
}

// Point::setYCoord sets the value of the member variable YCoord
void Point::setYCoord(double yVal)
{
	YCoord = yVal;
}

// Point::getXCoord returns the value in member variable XCoord
double Point::getXCoord()
{
	return XCoord;
}

// Point::getYCoord returns the value in member variable YCoord
double Point::getYCoord()
{
	return YCoord;
}

// Point::distanceTo calculates and returns the distance from one point to another
double Point::distanceTo(const Point& otherPoint)
{
	// local variables used to calculate distance
	double xVal1,
		   xVal2,
		   yVal1,
		   yVal2;
	double distanceX,
		   distanceY,
		   distanceSq,
		   distance;
	
	// initialize and assign values to local variables
	xVal1 = XCoord;
	xVal2 = otherPoint.XCoord;
	yVal1 = YCoord;
	yVal2 = otherPoint.YCoord;

	// calculate the distance between x-coords and the distance between y-coords
	distanceX = xVal1 - xVal2;
	distanceY = yVal1 - yVal2;

	// use pythagorean theorem to calculate the distance between the 2 points
	distanceSq = pow(distanceX,2) + pow(distanceY, 2);
	distance = sqrt(distanceSq);

	// return the distance calculated
	return distance;
}
