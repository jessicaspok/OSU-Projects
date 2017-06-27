/*********************************************************************
** Program Filename: Creature.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Creature class header file
*********************************************************************/

#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Die.hpp"
#include <string>
#include <iostream>

using namespace std;

class Creature
{
protected:
	int points;              
	int armor;               
	int strength;                
	bool showData;       
	string name;        
	string type;  

public:
	Creature();
	~Creature();

	virtual int attack() = 0;
	virtual int defend(int) = 0;
	virtual void recover() = 0;

	int defensePrint(string, string, int, int);
	void addPoints(int);

	/* accessors */
	int getPoints();
	int getArmor();
	int getstrength();
	bool getShowData();
	string getName();
	string getType();

	/* mutators */
	void setPoints(int);
	void setArmor(int);
	void setstrength(int);
	void setShowData(bool);
	void setName(string);
	void setType(string);
};

#endif