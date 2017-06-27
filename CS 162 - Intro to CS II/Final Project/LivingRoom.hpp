/*********************************************************************
** Program Filename: LivingRoom.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: LivingRoom subclass header file
*********************************************************************/
#ifndef LIVINGROOM_HPP
#define LIVINGROOM_HPP

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

class LivingRoom : public Space
{
public:
	LivingRoom(Player *p);
	int option();
};

#endif 