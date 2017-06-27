/*********************************************************************
** Program Filename: main.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: shows user menu, validates, and calls game class
** Input: user selections for players
** Output: menu 
*********************************************************************/

#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	/* player selection variables */
	int p1;    
	int p2;    

	/* menu of choices */
	do {
		system("clear");
		
		/* select p1 creature */
		cout << "Creature Combat - Here are the available creature types: " 
			<< endl << endl << " 1: Medusa" << endl << " 2: Barbarian" 
			<< endl << " 3: Vampire" << endl << " 4: Blue Men" << endl
			<< " 5: Harry Potter" << endl << endl
			<< "Please select creature type for player 1, or press 6 to quit: ";

		cin >> p1;

		/* input validation */
		while (p1 < 1 || p1 > 6)
		{
			cout << endl << "Choose a number from 1 - 6: ";
			cin >> p1;
		}

		/* select p2 creature */
		if (p1 != 6)
		{
			cout << endl << " 1: Medusa" << endl << " 2: Barbarian" << endl 
				<< " 3: Vampire" << endl << " 4: Blue Men" << endl << 
				" 5: Harry Potter" << endl << endl  
				<< "Please select creature type for player 2: ";
			
			cin >> p2;

			/* input validation */
			while (p2 < 1 || p2 > 5)
			{
				cout << endl << "Choose a number from 1 - 5: ";
				cin >> p2;
			}

			/* create game and pass in the selected creatures */
			Game newGame(p1, p2);
			newGame.play();
		}
	} while (p1 != 6);

	return 0;
}