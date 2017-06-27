/*****************************************************************
** Author: Jessica Spokoyny
** Date: August 4, 2015
** Description: This is a header file for the class Item
******************************************************************/

#include <string>
using namespace std;

#ifndef ITEM_HPP
#define ITEM_HPP

class Item
{
	private:     
		string name;
		double price;
		int quantity;

	public:
		Item();						// default constructor
		Item(string, double, int);	// constructor
		void setName(string);		// mutator function
		string getName();			// accessor function
		void setPrice(double);		// mutator function
		double getPrice();			// accessor function
		void setQuantity(int);		// mutator function
		int getQuantity();			// accessor function
};

#endif
