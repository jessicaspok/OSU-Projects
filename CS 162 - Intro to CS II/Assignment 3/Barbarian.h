/*********************************************************************
** Program Filename: Barbarian.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Barbarian derived class header file
*********************************************************************/

#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "Creature.h"
#include <iostream>
using namespace std;

class Barbarian : public Creature
{
private:
	Die *six_sided_die;  

public:
	Barbarian();
	~Barbarian();

	int attack();
	void defend(int);
};

#endif