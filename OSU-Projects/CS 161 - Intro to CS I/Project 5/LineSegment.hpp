/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 23, 2015
** Description: This is a header file for the class LineSegment
***************************************************************************/

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "Point.hpp"

class LineSegment
{
	private:
		Point p1;					
		Point p2;
	public:
		LineSegment();				// default constructor
		LineSegment(Point, Point);	// constructor		
		void setEnd1(Point);		// mutator function
		Point getEnd1();			// accessor function
		void setEnd2(Point);		// mutator function
		Point getEnd2();			// accessor function
		double length();			// returns length of the line segment
		double slope();				// returns slope of the line segment
};

#endif
