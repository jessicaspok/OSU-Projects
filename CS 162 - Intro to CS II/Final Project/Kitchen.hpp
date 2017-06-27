/*********************************************************************
** Program Filename: Kitchen.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Kitchen subclass header file
*********************************************************************/
#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

class Kitchen : public Space
{
public:
	Kitchen(Player *p);
	int option();
};

#endif 