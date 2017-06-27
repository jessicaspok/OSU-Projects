/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 23, 2015
** Description: This is a header file for the class called Point 
***************************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
	private:
		double XCoord;
		double YCoord;
	public:
		Point();							// default constructor
		Point(double xVal, double yVal);	// constructor
		void setXCoord(double);				// mutator function
		double getXCoord();					// accessor function
		void setYCoord(double);				// mutator function
		double getYCoord();					// accessor function
		double distanceTo(const Point&);	// calculates the distance to another Point	
};

#endif
