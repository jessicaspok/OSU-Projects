/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 17, 2015
** Description: This function takes 3 int parameters by reference and sorts their values into ascending order
***************************************************************************/

void smallSort(int &a, int &b, int &c)
{
	// swaps a and b values if a>b
	if(a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	// swaps a and c values if a>c
	if(a > c)
	{
		int temp = a;
		a = c;
		c = temp;
	}

	// swaps b and c values if b>c
	if(b > c)
	{
		int temp = b;
		b = c;
		c = temp;
	}
}

/* main function used for testing

#include <iostream>
using namespace std;
int main()
{
	cout << "Enter three integers: " << endl;
	int num1, num2, num3;
	cin >> num1 >> num2 >> num3;

	smallSort(num1, num2, num3);

	cout << num1 << ", " << num2 << ", " << num3 << endl;
	
	return 0;
}
*/
