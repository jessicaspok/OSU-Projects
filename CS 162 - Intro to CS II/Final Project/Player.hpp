/*********************************************************************
** Program Filename: Player.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Player class header file
*********************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <string>

using namespace std;

class Player
{
private:
	bool hasKey;
	bool hasSH;
	bool escaped;
	string backpack[2];
	int count;
public:
	Player();
	void addItem(string);
	bool getKey();
	bool getSH();
	void setEscaped();
	bool getEscaped();
};

#endif