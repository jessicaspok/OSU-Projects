/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 7, 2015
** Description: This program will prompt the user for 2 integers then add up all the integers between them (inclusive) and display the total.
***************************************************************************/

#include<iostream>
using namespace std;

int main()
{
   int num1, num2, total, counter=1;

   // prompts user for input
   cout << "Please enter two integers: \n";
   cin >> num1;
   cin >> num2;

   // when the first int is smaller than the second
   if (num1<num2)
   {
      // set counter to equal smaller number
      // counter increases by 1 each iteration
      // keeps repeating until counter equals larger number
      // total adds the new counter to current total
      for (counter = num1; counter <= num2; counter++)   
      total += counter;
      cout << "The sum of the values in that range is: \n";
      cout << total << endl;
   }

   // when the first int is larger than the second
   else if (num1>num2)
   {
      // same procedure as for-loop above
      for (counter = num2; counter <= num1; counter++)
      total += counter;
      cout << "The sum of the values in that range is: \n";
      cout << total << endl;
   }
   
   // only other scenario is when the numbers are the same
   else 
   {
      total = num1;
      cout << "The sum of the values in that range is: \n";
      cout << total << endl;
   }

   return 0;
}
