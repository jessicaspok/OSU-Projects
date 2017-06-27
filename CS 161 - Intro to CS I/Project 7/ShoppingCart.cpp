/*****************************************************************
** Author: Jessica Spokoyny
** Date: August 4, 2015
** Description: This is a source file for the class ShoppingCart
******************************************************************/

#include "ShoppingCart.hpp"
using namespace std;

// default constructor
ShoppingCart::ShoppingCart()		
{
	arrayEnd = 0;

	for (int i = 0; i < SIZE; i++)
	{
		itemArray[i] = NULL;
	}
}

// place newItem in next empty spot of itemArray & 
// increase index of next empty spot in the array
void ShoppingCart::addItem(Item *newItem)
{
	itemArray[arrayEnd] = newItem;
	
	arrayEnd++;
}

// calculate and return total price
double ShoppingCart::totalPrice()
{
	// initialize the totalPrice to 0
	double totalPrice = 0;
	
	// loop through the array- for each item use accessor functions
	// to get quantity and price per unit - multiplt them together to get
	// totalPrice and keep a running total
	for (int i = 0; i < arrayEnd; i++)
	{
		totalPrice += itemArray[i]->getQuantity()*itemArray[i]->getPrice();
	}

	return totalPrice;

}
