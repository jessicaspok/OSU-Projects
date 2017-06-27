/*********************************************************************
** Program Filename: Queue.hpp
** Author: Jessica Spokoyny
** Date: 02/28/1602/12/2016
** Description: Queue header file
*********************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "Creature.hpp"

class Queue
{
private:
	struct QueueNode
	{
		Creature *data;  
		QueueNode *next;      
		QueueNode *prev;    
	};

	QueueNode *front;      
	QueueNode *back;     

public:
	Queue();
	~Queue();
	void add(Creature *);
	void remove();
	void print();

	Queue::QueueNode * getFront();
};

#endif