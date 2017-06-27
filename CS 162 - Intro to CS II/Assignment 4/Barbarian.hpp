/*********************************************************************
** Program Filename: Barbarian.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Barbarian derived class header file
*********************************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "Creature.hpp"
#include <iostream>

using namespace std;

class Barbarian : public Creature
{
private:
	Die *six_sided_die;

public:
	Barbarian(string, bool);
	~Barbarian();

	int attack();
	int defend(int);
	void recover();
};

#endif