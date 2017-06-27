/****************************************************************************************** Author: Jessica Spokoyny
** Date: July 1, 2015
** Description: This program calculates the fewest number of coins needed
****************************************************************************************/

#include <iostream>
using namespace std;

int main()
{
   int cents, quarters, dimes, nickels, pennies;
   
   // Gets the cents value from the user
   cout << "Please enter an amount in cents less than a dollar. \n";
   cin >> cents;

   // Calculate how many quarters needed
   quarters = cents/25;

   // Calculate how many dimes needed
   dimes = (cents%25)/10;

   // Calculate how many nickels needed
   nickels = ((cents%25)%10)/5;

   // Calculate how many pennies needed
   pennies = (((cents%25)%10)%5);

   // Displays coins needed
   cout << "Your change will be: \n";
   cout << "Q: " << quarters << endl;
   cout << "D: " << dimes << endl;
   cout << "N: " << nickels << endl;
   cout << "P: " << pennies << endl;

   return 0;

}
