/*********************************************************************
** Program Filename: Medusa.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Medusa derived class header file
*********************************************************************/

#ifndef MEDUSA_H
#define MEDUSA_H

#include "Creature.h"
#include <iostream>
using namespace std;

class Medusa : public Creature
{
private:
	Die *six_sided_die;    

public:
	Medusa();
	~Medusa();

	int attack();
	void defend(int);
};

#endif