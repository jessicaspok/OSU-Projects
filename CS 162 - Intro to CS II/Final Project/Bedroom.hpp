/*********************************************************************
** Program Filename: Bedroom.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Bedroom subclass header file
*********************************************************************/
#ifndef BEDROOM_HPP
#define BEDROOM_HPP

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

class Bedroom : public Space
{
public:
	Bedroom(Player *p);
	int option();
};
#endif 