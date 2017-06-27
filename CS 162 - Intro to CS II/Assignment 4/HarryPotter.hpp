/*********************************************************************
** Program Filename: HarryPotter.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: HarryPotter derived class header file
*********************************************************************/

#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP

#include "Creature.hpp"
#include <iostream>
using namespace std;

class HarryPotter : public Creature
{
private:
	bool hogwarts;
	Die *six_sided_die;

public:
	HarryPotter(string, bool);
	~HarryPotter();

	int attack();
	int defend(int);
	void recover();

	/* accessors */
	bool getHogwarts();

	/* mutators */
	void setHogwarts(bool);
};

#endif