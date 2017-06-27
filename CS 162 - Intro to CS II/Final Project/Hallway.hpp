/*********************************************************************
** Program Filename: Hallway.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: Hallway subclass header file
*********************************************************************/
#ifndef HALLWAY_HPP
#define HALLWAY_HPP

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

class Hallway : public Space
{
public:
	Hallway(Player *p);
	int option();
};

#endif