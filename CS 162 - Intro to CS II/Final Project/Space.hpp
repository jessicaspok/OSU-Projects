/*********************************************************************
** Program Filename: Space.hpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description:  Space class header file
*********************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP

#include <stdio.h>
#include <string>
#include <iostream>
#include "Player.hpp"

using namespace std;

class Space
{
protected:
	Space *space1;
	Space *space2;
	Space *space3;
	Space *space4;
	Player *player;                                     

public:
	Space();                                            
	Space(Player *p);                                   
	virtual int option() = 0;                         
	virtual Space* getSpace(int);                    
	virtual void addSpace(Space *one, Space *two, Space *three, Space *four);
};
#endif