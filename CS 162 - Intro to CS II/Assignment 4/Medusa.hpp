/*********************************************************************
** Program Filename: Medusa.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Medusa derived class header file
*********************************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include "Creature.hpp"
#include <iostream>
using namespace std;

class Medusa : public Creature
{
private:
	Die *six_sided_die;

public:
	Medusa(string, bool);
	~Medusa();

	int attack();
	int defend(int);
	void recover();
};

#endif