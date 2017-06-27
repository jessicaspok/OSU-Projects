/*********************************************************************
** Program Filename: Die.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Die class header file
*********************************************************************/

#ifndef DIE_HPP
#define DIE_HPP

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