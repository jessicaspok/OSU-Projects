/*********************************************************************
** Program Filename: Item.h
** Author: Jessica Spokoyny
** Date: 01/29/15
** Description: Item class header file
*********************************************************************/

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <array>

using namespace std;

class Item
{
private:
	string itemName;
	string units;
	int numberToBuy;
	double unitPrice;
public:
	/* constructors */
	Item(string, string, int, double);
	Item();

	/* mutators */
	void setItemName(string);
	void setUnits(string);
	void setNumberToBuy(int);
	void setUnitPrice(double);
	
	/* accessors */
	string getItemName();
	string getUnits();
	int getNumberToBuy();
	double getUnitPrice();

	/* overloaded operator */
	bool operator==(Item& rhs);
	
};

#endif
