/*********************************************************************
** Program Filename: BlueMen.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: BlueMen derived class header file
*********************************************************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

#include "Creature.hpp"
#include <iostream>

using namespace std;

class BlueMen : public Creature
{
private:
	Die *six_sided_die;
	Die *ten_sided_die;

public:
	BlueMen(string, bool);
	~BlueMen();

	int attack();
	int defend(int);
	void recover();
};

#endif