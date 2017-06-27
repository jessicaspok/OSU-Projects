/*********************************************************************
** Program Filename: HarryPotter.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: HarryPotter derived class header file
*********************************************************************/

#ifndef HARRYPOTTER_H
#define HARRYPOTTER_H

#include "Creature.h"
#include <iostream>
using namespace std;

class HarryPotter : public Creature
{
private:
	bool hogwarts;
	Die *six_sided_die;   

public:
	HarryPotter();
	~HarryPotter();

	int attack();
	void defend(int);

	/* accessors */
	bool getHogwarts();

	/* mutators */
	void setHogwarts(bool);
};

#endif