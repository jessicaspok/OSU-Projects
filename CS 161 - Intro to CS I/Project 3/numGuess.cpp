/********************************************************************************* Author: Jessica Spokoyny
** Date: July 6, 2015
** Description: this program prompts the user for an integer that the player (maybe the user, maybe someone else) will try to guess. The program loops until the user guesses correctly. Then the program prints how many guesses it took. 
*******************************************************************************/
#include<iostream>

using namespace std;

int main()
{
   int number, guess;
   int count = 0;

   // prompt user for the number to guess
   cout << "Enter the number for the player to guess.\n";
   cin >> number;

   // prompt user for first guess
   cout << "Enter your guess.\n";

   // user guesses until the correct number is reached
   do
   {
      count++;
      cin >> guess;

      // guess was too high
      if (guess > number)
         cout << "Too high - try again.\n";

      // guess was too low
      else if (guess < number)
         cout << "Too low - try again. \n";
  
      // guess was correct
      else
         cout << "You guessed it in " << count << " tries.\n";
   }
   while (guess != number);

   return 0;	

}
