/*****************************************************************
** Author: Jessica Spokoyny
** Date: August 4, 2015
** Description: This is a source file for the class Item
******************************************************************/

#include "Item.hpp"
using namespace std;

// default constructor
Item::Item()
{
	setName("");
	setPrice(0.0);
	setQuantity(0);
}

// constructor
Item::Item(string s, double x, int y)
{
	setName(s);
	setPrice(x);
	setQuantity(y);
}

// Item::setName sets the name of the item
void Item::setName(string n)
{
	name = n;
}

// Item::getName returns the name of the item
string Item::getName()
{
	return name;
}

// Item::setPrice sets the price of the item
void Item::setPrice(double p)
{
	price = p;
}

// Item::getPrice returns the price of the item
double Item::getPrice()
{
	return price;
}

// Item::setQuantity sets the quantity of the item
void Item::setQuantity(int q)
{
	quantity = q;
}

// Item::getQuantity returns the quantity of the item
int Item::getQuantity()
{
	return quantity;
}

