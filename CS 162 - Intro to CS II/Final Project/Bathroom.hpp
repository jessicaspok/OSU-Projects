/*********************************************************************
** Program Filename: Bathroom.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Bathroom subclass header file
*********************************************************************/
#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

class Bathroom : public Space
{
public:
	Bathroom(Player *p);
	int option();
};
#endif 