/*********************************************************************
** Program Filename: Kitchen.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Kitchen subclass implementation file
*********************************************************************/
#include "Kitchen.hpp"

/*********************************************************************
** Function: constructor
** Description: creates Kitchen object, initializes all connected
**	spaces to null, sets p as player
** Paramters: pointer to a Player object
*********************************************************************/
Kitchen::Kitchen(Player *p)
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
int Kitchen::option()
{
	int userChoice = 0;

	while (!(userChoice == 1 || userChoice == 2)) 
	{
		int shelfChoice = 0;
		
		/* kitchen menu */
		cout << endl << "***********************************************"
			<< endl << " Kitchen "
			<< endl << "***********************************************"
			<< endl << "	Press 1 to go into the hallway" 
			<< endl << "	Press 2 to go into the living room" 
			<< endl << "	Press 3 to check out the shelves" << endl;
		cin >> userChoice;

		/* shelf menu */
		if (userChoice == 3)
		{
			while (shelfChoice != 2) 
			{
				int boxChoice = 0;
				cout << endl << "You see a small tin box on one of the shelves" 
					<< endl << endl << "	Press 1 to inspect it" 
					<< endl << "	Press 2 to leave the shelf area" << endl;
				cin >> shelfChoice;

				/* box and key menu */
				if (shelfChoice == 1 && !player->getKey()) 
				{
					while (boxChoice != 1) 
					{
						/* player doesn't have key */
						if (!player->getKey()) 
						{
							cout << endl << "As you pick up the box, you hear a "
								<< "clanking noise.. it's a key! " << endl
								<< "This could be useful in your escape.." << endl
								<< endl << "	Press 1 to put the key and box back" 
								<< " on the shelf" << endl 
								<< "	Press 2 to take the key" << endl;
						}

						cin >> boxChoice;

						/* take key */
						if (boxChoice == 2 && !player->getKey()) 
						{
							player->addItem("key");
							cout << endl 
								<< "The key has been placed in your backpack"
								<< endl;
							boxChoice = 1;
							shelfChoice = 2;
							cout << endl << "Leaving the shelf area.." << endl;
						}
					}
				}

				/* player already has key */
				else if (shelfChoice == 1 && player->getKey())
				{
					cout << endl << "You pick up the box, but there is nothing "
						<< "inside.." << endl;
					shelfChoice = 2;
					cout << endl << "Leaving the shelf area.." << endl;
				}

				/* leave shelf area */
				else if (shelfChoice == 2)
				{
					cout << endl << "Leaving the shelf area.." << endl;
				}
			}
		}

	}

	/* go to hallway */
	if (userChoice == 1) 
	{
		return 1;                   
	}

	/* go to living room */
	else
	{
		return 2;                   
	}
}