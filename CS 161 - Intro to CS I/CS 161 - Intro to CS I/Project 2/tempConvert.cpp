/********************************************************************************* Author: Jessica Spokoyny
** Date: July 1, 2015
** Description: This program converts Celsius temperatures to Farenheit 
*******************************************************************************/

#include <iostream>
using namespace std;

int main()
{
   double cel, far;

   // Get the Celsius temp
   cout << "Please enter a Celsius temperature. \n";
   cin >> cel;

   // Compute and display the Farenheit temp
   far = ((9*cel)/5 + 32);
   cout << "The equivalent Farenheit temperature is: \n";
   cout << far << endl;

   return 0;

}
