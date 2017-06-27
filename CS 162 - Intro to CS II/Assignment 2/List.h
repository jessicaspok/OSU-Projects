/*********************************************************************
** Program Filename: List.h
** Author: Jessica Spokoyny
** Date: 01/29/15
** Description: List class header file
*********************************************************************/

#ifndef LIST_H
#define LIST_H

#include "Item.h"

class List
{
private:
	Item* groceryList;
	int capacity;
	int itemCount;

public:
	/* constructor */
	List();

	/* destructor */
	~List();

	/* add item function */
	void addItem(Item &tmp);

	/* remove item function */
	void removeItem(Item &tmp);
	
	/* total price function */
	double getTotalPrice();

	/* get count function */
	int getCount();

	/* print list function */
	void printList();
	
};

#endif
