/*********************************************************************
** Program Filename: Stack.hpp
** Author: Jessica Spokoyny
** Date: 02/28/1602/12/2016
** Description: Stack header file
*********************************************************************/

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Creature.hpp"

class Stack
{
private:
	struct StackNode
	{
		Creature *data;     
		StackNode *next;    
	};

	StackNode *top;      

public:
	Stack();
	~Stack();

	void add(Creature *);
	void remove();
	void print();
};

#endif