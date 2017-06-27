/*********************************************************************
** Program Filename: Die.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Die class implementation file
** Input: number of sides
** Output: roll value
*********************************************************************/

#include "Die.hpp"
#include <cstdlib>

/*********************************************************************
** Function: default constructor
** Description: creates a die with 6 sides
** Paramters: None
*********************************************************************/
Die::Die()
{
	setSides(6);
}

/*********************************************************************
** Function: constructor
** Description: creates a die with s number of sides
** Parameters: int number of sides
*********************************************************************/
Die::Die(int s)
{
	setSides(s);
}

/*********************************************************************
** Function: setSides
** Description: set number of sides for the die
** Parameters: int number of sides
*********************************************************************/
void Die::setSides(int s)
{
	sides = s;
}

/*********************************************************************
** Function: getSides
** Description: get number of sides from the die
** Parameters: none
*********************************************************************/
int Die::getSides()
{
	return sides;
}

/*********************************************************************
** Function: roll()
** Description: rolls the die and returns an int value
** Parameters: None
** Pre-Conditions: rand must be seeded first
** Post-Conditions: returns an int value of the roll
*********************************************************************/
int Die::roll()
{
	return rand() % sides + 1;
}
