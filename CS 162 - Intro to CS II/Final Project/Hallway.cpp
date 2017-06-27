/*********************************************************************
** Program Filename: Hallway.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Hallway subclass implementation file
*********************************************************************/
#include "Hallway.hpp"

/*********************************************************************
** Function: constructor
** Description: creates Hallway object, initializes all connected
**	spaces to null, sets p as player
** Paramters: pointer to a Player object
*********************************************************************/
Hallway::Hallway(Player *p)
{
	space1 = NULL;
	space2 = NULL;
	space3 = NULL;
	space4 = NULL;
	player = p;
}

/*********************************************************************
** Function: option
** Description: displays appropriate menu for current space
** Parameters: none
** Pre-Conditions: current space has been initialized
** Post-Conditions: user selections are used to perform desired
**	actions then move on to next space
*********************************************************************/
int Hallway::option()
{
	int userChoice = 0;

	//Hallway menu choice
	while (!(userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4)) 
	{
		int closetChoice = 0;
		cout << endl << "***********************************************"
			<< endl << " Hallway " 
			<< endl << "***********************************************"
			<< endl << "	Press 1 to go into the bedroom" 
			<< endl << "	Press 2 to go into the bathroom" 
			<< endl << "	Press 3 to go into the kitchen" 
			<< endl << "	Press 4 to go into the living room" 
			<< endl << "	Press 5 to see what's inside the closet" << endl;
		cin >> userChoice;

		//Closet menu choice
		if (userChoice == 5 && !player->getSH())
		{
			while (closetChoice != 2) 
			{
				cout << endl << "You see an sledgehammer in the closet.. " 
					<< "this could be useful in your escape!" << endl
					<< endl << "	Press 1 to take the sledgehammer" << endl
					<< "	Press 2 to close the closet door" << endl;
				cin >> closetChoice;

				if (closetChoice == 1) 
				{
					player->addItem("sledgehammer");
					cout << endl << "The sledgehammer has been placed in your" 
						<< " backpack.." << endl
						<< endl << "Closing the closet door.." << endl;
					closetChoice = 2;
				}

				else if (closetChoice == 2)
				{
					cout << endl << "Closing the closet door.." << endl;
				}
			}
		}
		else if (userChoice == 5 && player->getSH())
		{
			cout << endl << "The closet is empty.. " << endl
				<< endl << "Closing the closet door.." << endl;
		}
	}

	if (userChoice == 1) 
	{
		return 1;                               //Return 1 for Space 1
	}

	else if (userChoice == 2)
	{
		return 2;                               //Return 2 for Space 2
	}

	else if (userChoice == 3)
	{
		return 3;                               //Return 3 for Space 3
	}

	else
	{
		return 4;                               //Return 4 for Space 4
	}
}