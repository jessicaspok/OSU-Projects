/*********************************************************************
** Program Filename: Bathroom.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Bathroom subclass implementation file
*********************************************************************/
#include "Bathroom.hpp"

/*********************************************************************
** Function: constructor
** Description: creates Bathroom object, initializes all connected 
**	spaces to null, sets p as player
** Paramters: pointer to a Player object
*********************************************************************/
Bathroom::Bathroom(Player *p)
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
int Bathroom::option()
{
	int userChoice = 0;

	while (userChoice != 1)
	{
		/* bathroom menu */
		cout << endl << "***********************************************"
			<< endl << " Bathroom "
			<< endl << "***********************************************"
			<< endl << "	Press 1 to go into the hallway"
			<< endl << "	Press 2 to check out the window" << endl;

		cin >> userChoice;

		if (userChoice == 2) 
		{
			/* window menu */
			while (userChoice != 1) 
			{
				cout << endl << "The window is locked and there is no key in sight."
					<< endl << endl << "	Press 1 to leave this room"
					<< endl << "	Press 2 to try breaking the window" << endl;
				cin >> userChoice;

				/* attempt to break window */
				if (userChoice == 2) 
				{
					/* player has sledgehammer and breaks window */
					if (player->getSH() == true) 
					{
						cout << endl << "You use the sledgehammer to smash through"
							<< " the glass" << endl << "and you climb out of the"
							<< " window!" << endl;
						player->setEscaped();
						return 10;
					}

					/* player does not have sledgehammer and dog hears */
					else if (player->getSH() == false)
					{
						cout << endl << "You made too much noise trying to break "
							<< "the window and the dog attacks you.. " << endl
							<< "Now, you can't escape in time." << endl;
						return 9;
					}
				}
			}
		}
	}

	/* go to hallway */
	return 1;  
}