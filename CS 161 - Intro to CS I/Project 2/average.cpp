/********************************************************************************* Author: Jessica Spokoyny
** Date: July 1, 2015
** Description: Program that calculates the average of 5 numbers
*******************************************************************************/

#include <iostream>
using namespace std;

int main()
{
   double num1, num2, num3, num4, num5, average;

   // Get the five numbers
   cout << "Please enter five numbers." << endl;
   cin >> num1; 
   cin >> num2; 
   cin >> num3; 
   cin >> num4; 
   cin >> num5;

   // Computes the average
   average = (num1 + num2 + num3 + num4 + num5)/5;

   // Displays the average
   cout << "The average of those numbers is: \n";
   cout << average << endl;

   return 0;

}
