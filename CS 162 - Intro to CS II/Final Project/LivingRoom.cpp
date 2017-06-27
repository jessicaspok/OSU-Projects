/*********************************************************************
** Program Filename: LivingRoom.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: LivingRoom subclass implementation file
*********************************************************************/
#include "LivingRoom.hpp"

/*********************************************************************
** Function: constructor
** Description: creates LivingRoom object, initializes all connected
**	spaces to null, sets p as player
** Paramters: pointer to a Player object
*********************************************************************/
LivingRoom::LivingRoom(Player *p)
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
int LivingRoom::option()
{
	int userChoice = 0;
	
	/* living room menu */
	while (!(userChoice == 1 || userChoice == 2))
	{
		cout << endl << "***********************************************"
			<< endl << " Living Room "
			<< endl << "***********************************************"
			<< endl << "	Press 1 to go into the hallway" 
			<< endl << "	Press 2 to go into the kitchen" 
			<< endl << "	Press 3 to check out the front door" << endl;
		cin >> userChoice;

		/* front door menu */
		if (userChoice == 3) 
		{
			/* player has key and uses front door */
			if (player->getKey() == true) 
			{
				cout << endl << "The door is locked.. "
					<< endl << "You take the key out of your backpack and try it.." 
					<< endl << "It worked! You have escaped!" << endl;
				player->setEscaped();
				return 10;                  
			}

			/* player does not have key and attempts front door */
			else
			{
				cout << endl << "The door is locked.. try another way out!" << endl;
			}
		}
	}

	/* go to hallway */
	if (userChoice == 1) 
	{
		return 1;                           
	}

	/* go to kitchen */
	else
	{
		return 2;                           
	}
}