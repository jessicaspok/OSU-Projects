/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 7, 2015
** Description: This program asks the user how many integers they would like to enter. Then it prompts the user to enter that many integers. After all the numbers have been entered, the program displays the largest and smallest of those numbers
***************************************************************************/

#include<iostream>

using namespace std;

int main()
{
   int n, count, num, max, min;
   
   // prompts user for number of integers
   cout << "How many integers would you like to enter? \n";
   cin >> n;

   // prompts user for the integers
   cout << "Please enter " << n << " integers.\n";

   // initializes the counter
   // keeps repeating every time that the counter is less than n
   // counter increases by 1 after each iteration
   for (count = 0; count < n; count++)
   {
      // user enters an int
      cin >> num;
      
      // the first int entered will be the min and max
      if (count==0)
      {
         max=min=num;
      }

      // if the next number entered is bigger than max, it will replace max
      if (num > max)
      {
         max = num;
      }

      // if the next number entered is smaller than min, it will replace min
      if (num < min)
      {
         min = num;
      }
   }

   // displays max and min values
   cout << "min: " << min << endl;
   cout << "max: " << max << endl;

   return 0;
}

