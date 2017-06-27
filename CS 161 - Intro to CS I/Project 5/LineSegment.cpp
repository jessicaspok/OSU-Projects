/*************************************************************************************
** Author: Jessica Spokoyny
** Date: July 23, 2015
** Description: This is the member function implementation section of the class
** LineSegment
*************************************************************************************/

#include "LineSegment.hpp"

// constructor
LineSegment::LineSegment(Point p1, Point p2)
{
	setEnd1(p1);
	setEnd2(p2);
}

// LineSegment::setEnd1 sets the value of the Point p1
void LineSegment::setEnd1(Point p)
{
	p1 = p;
}

// LineSegment::getEnd1 returns the value in Point p1
Point LineSegment::getEnd1()
{
	return p1;
}

// LineSegment::setEnd2 sets the value of the Point p2
void LineSegment::setEnd2(Point p)
{
	p2 = p;
}

// LineSegment::getEnd2 returns the value in Point p2
Point LineSegment::getEnd2()
{
	return p2;
}

// calculate and return the length of the line segment
double LineSegment::length()
{
	return p1.distanceTo(p2);
}

// calculate and return the slope of the line segment
double LineSegment::slope()
{
	// local variables to calculate change in x and change in y
	double rise = p2.getYCoord() - p1.getYCoord();
	double run = p2.getXCoord() - p1.getXCoord();

	// calculate and return the value for the slope
	return rise/run;
}
