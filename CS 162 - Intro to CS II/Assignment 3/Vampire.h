/*********************************************************************
** Program Filename: Vampire.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Vampire derived class header file
*********************************************************************/

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Creature.h"
#include <iostream>
using namespace std;

class Vampire : public Creature
{
private:
	Die *six_sided_die;
	Die *twelve_sided_die;     

public:
	Vampire();
	~Vampire();

	int attack();
	void defend(int);
};

#endif