#include <iostream>

#include "Point.hpp"
#include "LineSegment.hpp"

using namespace std;

int main()
{
	Point p1;

	// testing 3-4-5 triangle
	p1.setXCoord(-1.5);
	p1.setYCoord(0.0);
	Point p2(1.5,4.0);
	double dist = p1.distanceTo(p2);
	cout << "distance = " << dist << endl;

	// testing line segment
	p1 = Point(4.3,7.52);
	p2 = Point(-17.0, 1.5);
	LineSegment ls1(p1, p2);
	double length = ls1.length();
	double slope = ls1.slope();

	cout << "length = " << length << endl;
	cout << "slope = " << slope << endl;

	return 0;
}
