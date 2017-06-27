/*****************************************************************
** Author: Jessica Spokoyny
** Date: August 4, 2015
** Description: This is a header file for the class ShoppingCart
******************************************************************/

#include "Item.hpp"

#ifndef SHOPPINGCART_HPP
#define SHOPPINGCART_HPP


class ShoppingCart
{
	private:
		static const int SIZE = 100;	// max array size
		Item *itemArray[SIZE];			// Item array
		int arrayEnd;					// index of next empty spot in array

	public:
		ShoppingCart();					// default constructor
		void addItem(Item*);			// adds the item to the array 
		double totalPrice();			// returns the total price
};

#endif
