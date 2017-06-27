/*********************************************************************
** Program Filename: BlueMen.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: BlueMen derived class header file
*********************************************************************/

#ifndef BLUEMEN_H
#define BLUEMEN_H

#include "Creature.h"
#include <iostream>
using namespace std;

class BlueMen : public Creature
{
private:
	Die *six_sided_die;
	Die *ten_sided_die;    

public:
	BlueMen();
	~BlueMen();

	int attack();
	void defend(int);
};

#endif