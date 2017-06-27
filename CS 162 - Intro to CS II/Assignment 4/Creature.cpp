/*********************************************************************
** Program Filename: Creature.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Creature class implementation file
** Input: armor, strength, and name for a creature
** Output: returns values for armor, strength, and name
*********************************************************************/

#include "Creature.hpp"

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
** Function: defensePrint
** Description: calculates and displays damage
** Paramters: string, string, int, int 
*********************************************************************/
int Creature::defensePrint(string name, string type, int attack_damage, int defense)
{
	/* subtract defense from attack damage */
	int damage = attack_damage - defense;

	/* damage cannot be negative */
	if (damage < 0)
	{
		damage = 0;
	}
	
	/* subtract damage from strength */
	strength -= damage;

	/* strength cannot be negative */
	if (strength < 0)
	{
		strength = 0;
	}

	if (showData)
	{
		cout << type << " " << name << "'s defense: " << defense << endl;
		cout << "Attack total damage: " << damage << endl;
		cout << type << " " << name << " has " << strength 
			<< " strength points remaining." << endl;
	}

	return damage;
}

/*********************************************************************
** Function: addPoints
** Description: adds points to that creature's score
** Paramters: int
*********************************************************************/
void Creature::addPoints(int p)
{
	this->points += p;
}

/*********************************************************************
** Function: getPoints
** Description: accessor function that returns points of that creature
** Paramters: None
*********************************************************************/
int Creature::getPoints()
{
	return points;
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
int Creature::getstrength()
{
	return strength;
}

/*********************************************************************
** Function: getShowData
** Description: accessor function that returns t/f for show data
** Paramters: None
*********************************************************************/
bool Creature::getShowData()
{
	return showData;
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
** Function: getType
** Description: accessor function that returns type of that creature
** Paramters: None
*********************************************************************/
string Creature::getType()
{
	return type;
}

/*********************************************************************
** Function: setPoints
** Description: mutator function that sets the points for that creature
** Paramters: int
*********************************************************************/
void Creature::setPoints(int p)
{
	this->points = p;
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
void Creature::setstrength(int strength)
{
	this->strength = strength;
}

/*********************************************************************
** Function: setShowData
** Description: mutator function that sets t/f for showing data
** Paramters: bool
*********************************************************************/
void Creature::setShowData(bool s)
{
	this->showData = s;
}

/*********************************************************************
** Function: setName
** Description: mutator function that sets the name for that creature
** Paramters: string
*********************************************************************/
void Creature::setName(string n)
{
	this->name = n;
}

/*********************************************************************
** Function: setType
** Description: mutator function that sets the name for that creature
** Paramters: string
*********************************************************************/
void Creature::setType(string t)
{
	this->type = t;
}