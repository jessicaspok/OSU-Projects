/*********************************************************************
** Program Filename: Creature.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Creature class implementation file
** Input: armor, strength, and name for a creature
** Output: returns values for armor, strength, and name
*********************************************************************/

#include "Creature.h"

/*********************************************************************
** Function: default constructor
** Description: not used because it's abstract
** Paramters: None
*********************************************************************/
Creature::Creature() 
{
}

/*********************************************************************
** Function: destructor
** Description: not used because it's abstract
** Paramters: None
*********************************************************************/
Creature::~Creature() 
{
}

/*********************************************************************
** Function: getArmor
** Description: accessor function that returns armor of that creature
** Paramters: None
*********************************************************************/
int Creature::getArmor()
{
	return armor;
}

/*********************************************************************
** Function: getStrength
** Description: accessor function that returns strength of that 
**	creature
** Paramters: None
*********************************************************************/
int Creature::getStrength()
{
	return strength;
}

/*********************************************************************
** Function: getName
** Description: accessor function that returns name of that creature
** Paramters: None
*********************************************************************/
string Creature::getName()
{
	return name;
}

/*********************************************************************
** Function: setArmor
** Description: mutator function that sets the armor for that creature
** Paramters: int
*********************************************************************/
void Creature::setArmor(int a)
{
	this->armor = a;
}

/*********************************************************************
** Function: setStrength
** Description: mutator function that sets the strength for that 
**	creature
** Paramters: int
*********************************************************************/
void Creature::setStrength(int s)
{
	this->strength = s;
}

/*********************************************************************
** Function: setName
** Description: mutator function that sets the name for that creature
** Paramters: int
*********************************************************************/
void Creature::setName(string n)
{
	this->name = n;
}