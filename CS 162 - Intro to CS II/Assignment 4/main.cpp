/***************************************************************************
** Program Filename: Main.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: main driver function for creature combat tournament
***************************************************************************/

#include <iostream>
#include <cstdlib>
#include "Game.hpp"

int main()
{
	int choice;      
	char data;        
	bool showData;   

	do
	{
		/* menu */
		system("clear");
		cout << "Creature Combat Tournament: " << endl;
		cout << "Please select how many players you want on each team," 
			 << "or press 0 to quit." << endl;
		cin >> choice;

		/* input validation */
		while (choice < 0 || choice > 100)
		{
			cout << "Please enter a choice between 0 and 100." << endl;
			cin >> choice;
		}

		if (choice != 0)
		{
			cout << "Would you like to see the details of each round of combat? (y/n): ";
			cin >> data;

			/* input validation */
			while ((data != 'y' && data != 'Y') && (data != 'n' && data != 'N'))
			{
				cout << "Pleae enter a \"y\" or an \"n\"." << endl;
				cin >> data;
			}

			if (data == 'y' || data == 'Y')
			{
				showData = true;
			}

			else
			{
				showData = false;
			}

			Game myGame(choice, showData);
			myGame.init();
			myGame.play();
		}
	} while (choice != 0);

	return 0;
}
