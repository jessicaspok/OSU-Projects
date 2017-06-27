/*********************************************************************
** Program Filename: Die.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Die class header file
*********************************************************************/

#ifndef DIE_H
#define DIE_H

#include <cstdlib>
using namespace std;

class Die
{
protected:
	int sides;      

public:
	Die(); 
	Die(int);

	int roll();

	/* accessors */
	int getSides();

	/* mutators */
	void setSides(int);	
};

#endif