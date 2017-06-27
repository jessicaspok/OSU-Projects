/***************************************************************************** Author: Jessica Spokoyny
** Date: July 18, 2015
** Description: This function takes the starting integer as a parameter and returns how many steps it takes to reach 1 using the hailstone sequence
***************************************************************************/


int hailstone(int n)
{
	// Initialize counter to zero
	int count = 0;
	
	// Continue until n reaches 1
	while(n != 1)
	{	
		// n is even
		if(n % 2 == 0)
		{
			n = n/2;
			count++;
		}

		// n is odd
		else
		{
			n = (3*n) + 1;
			count++;
		}
	}
	
	return count;
}


/* used for testing the outputs and functionality of the program

#include <iostream>
using namespace std;

int main()
{
	int x;
	
	cout << "Enter a positive integer: ";
	
	cin >> x;

	cout << "Steps taken: " << hailstone(x) << endl;

	return 0;
}

*/
