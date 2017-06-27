/***************************************************************************
** Name: Jessica Spokoyny
** Date: July 15, 2015
** Description: this function takes the time an object has been falling and uses it to determine the distance the object has fallen. 
***************************************************************************/

double fallDistance(int t = 0)
{
	double d = 0;
	const double g = 9.8;
	
	// formula for calculating distance
	d = (0.5)*g*t*t;
	
	return d;
}

/* main function used for testing

#include<iostream>
using namespace std;

int main()
{
	int t = 0;
	double d = 0;

	cout << "seconds passed?: \n";
	cin >> t;
	
	d = fallDistance(t);
	
	cout << t << " seconds:   " << d << " meters\n"; 
	
	return 0;
}
*/
