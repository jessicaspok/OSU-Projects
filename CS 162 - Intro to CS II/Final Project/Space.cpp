/*********************************************************************
** Program Filename: Space.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description:  Space class implementation file
*********************************************************************/
#include "Space.hpp"

/*********************************************************************
** Function: default constructor
** Description: creates Space object, initializes all connected spaces
**	to null, sets player to null
** Paramters: None
*********************************************************************/
Space::Space()
{
	space1 = NULL;
	space2 = NULL;
	space3 = NULL;
	space4 = NULL;
	player = NULL;
}

/*********************************************************************
** Function: constructor
** Description: creates Space object, initializes all connected spaces
**	to null, sets p as player
** Paramters: pointer to a Player object
*********************************************************************/
Space::Space(Player *p)
{
	space1 = NULL;
	space2 = NULL;
	space3 = NULL;
	space4 = NULL;
	player = p;
}

/*********************************************************************
** Function: addSpace
** Description: sets connected spaces to their appropriate rooms
** Parameters: 4 pointers to space objects
** Pre-Conditions: pointers to space objects exist and are valid
** Post-Conditions: connecting rooms are set
*********************************************************************/
void Space::addSpace(Space *one, Space *two, Space *three, Space *four)
{
	space1 = one;
	space2 = two;
	space3 = three;
	space4 = four;
}

/*********************************************************************
** Function: getSpace
** Description: returns the value for the selected room
** Parameters: int
** Pre-Conditions: the int is valid
** Post-Conditions: next room to move to is chosen
*********************************************************************/
Space* Space::getSpace(int i)
{
	if (i == 1) 
	{
		return space1;
	}
	else if (i == 2)
	{
		return space2;
	}
	else if (i == 3)
	{
		return space3;
	}
	else
	{
		return space4;
	}
}