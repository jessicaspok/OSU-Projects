/*********************************************************************
** Program Filename: Creature.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Creature class header file
*********************************************************************/

#ifndef CREATURE_H
#define CREATURE_H

#include "Die.h"
#include <string>
using namespace std; 

class Creature
{
protected:
	int armor;          
	int strength;              
	string name;	

public:
	Creature();
	~Creature();

	virtual int attack() = 0;
	virtual void defend(int) = 0;

	/* accessors */
	int getArmor();
	int getStrength();
	string getName();

	/* mutators */
	void setArmor(int);
	void setStrength(int);
	void setName(string);
};

#endif