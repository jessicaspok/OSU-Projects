/*********************************************************************
** Program Filename: Vampire.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Vampire derived class header file
*********************************************************************/

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

#include "Creature.hpp"
#include <iostream>
using namespace std;

class Vampire : public Creature
{
private:
	Die *six_sided_die;
	Die *twelve_sided_die;

public:
	Vampire(string, bool);
	~Vampire();

	int attack();
	int defend(int);
	void recover();
};

#endif