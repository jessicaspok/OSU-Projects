/*********************************************************************
** Program Filename: Player.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Player class implementation file
*********************************************************************/
#include "Player.hpp"

/*********************************************************************
** Function: default constructor
** Description: creates a Player and initializes variables (player 
**	doesn't have sledgehammer or key
**	initializes count of items in backpack to 0.
** Paramters: None
*********************************************************************/
Player::Player()
{
	hasSH = false;
	hasKey = false;
	count = 0;
}

/*********************************************************************
** Function: addItem
** Description: adds selected item to player's backpack
** Parameters: string
** Pre-Conditions: string is valid
** Post-Conditions: passed in item is added
*********************************************************************/
void Player::addItem(string item)
{
	if (item == "key") 
	{
		backpack[count] = item;
		count++;
		hasKey = true;
	}
	else if (item == "sledgehammer")
	{
		backpack[count] = item;
		count++;
		hasSH = true;
	}
}

/*********************************************************************
** Function: getKey
** Description: return hasKey status
** Parameters: none
*********************************************************************/
bool Player::getKey()
{
	return hasKey;
}

/*********************************************************************
** Function: getSH
** Description: return hasSH status
** Parameters: none
*********************************************************************/
bool Player::getSH()
{
	return hasSH;
}

/*********************************************************************
** Function: setEscaped
** Description: set escape status to true
** Parameters: none
*********************************************************************/
void Player::setEscaped()
{
	escaped = true;
}

/*********************************************************************
** Function: getEscaped
** Description: return escaped status
** Parameters: none
*********************************************************************/
bool Player::getEscaped() 
{ 
	return escaped; 
}