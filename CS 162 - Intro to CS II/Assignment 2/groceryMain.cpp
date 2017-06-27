/*********************************************************************
** Program Filename: groceryMain.cpp
** Author: Jessica Spokoyny
** Date: 01/29/15
** Description: This program creates grocery shopping list where users
**	can create a list, add items, remove items, and display the list
** Input: name, units, quantity, and unit price for each item
** Output: printed list displaying all information and total price
*********************************************************************/

#include "List.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	/* create new list */
	List groceries;

	/* create and initialize variables for Items */
	string name = "";
	string units = "";
	int qty = 0;
	double unitPrice = 0.0;

	/* create and initialize choice variable */
	char choice = '0';

	/* create new Item  to store temp values */
	Item *temp = new Item();

	/* display menu */
	while (choice != '4')
	{
		cout << "Grocery List Program: " << endl;
		cout << "\tPress 1 to add an item " << endl;
		cout << "\tPress 2 to remove an item " << endl;
		cout << "\tPress 3 to print the list " << endl;
		cout << "\tPress 4 to quit the program " << endl;
		cout << endl << "Please enter your choice: ";
		cin >> choice;

		cin.ignore();

		switch (choice)
		{
		case '1':
		{
			/* prompt user for name, units, quantity, unit price */
			/* convert strings to UPPERCASE for easy comparisons */
			cout << endl;
			cout << "Please enter the name of the item you would like "
					<< "to add: ";
			getline(cin, name);

			cout << "Please enter the units this item comes in: ";
			getline(cin, units);

			cout << "Please enter the quantity needed: ";
			cin >> qty;
			
			cout << "Please enter the unit price: ";
			cin >> unitPrice;
			cout << endl;

			/* set these inputs to as temp's attributes */
			temp->setItemName(name);
			temp->setUnits(units);
			temp->setNumberToBuy(qty);
			temp->setUnitPrice(unitPrice);
			
			/* add this Item to the List */
			groceries.addItem(*temp);

			break;
		}

		case '2':
		{
			/* prompt user for name, units */
			cout << endl;
			cout << "Please enter the name of the item you would like "
					<< "to remove: ";
			getline(cin, name);

			cout << endl;
			cout << "Please enter the units of the item you would like "
					<< "to remove: ";
			getline(cin, units);

			/* set these inputs to as temp's attributes */
			temp->setItemName(name);
			temp->setUnits(units);

			/* remove this Item from the List */
			groceries.removeItem(*temp);

			break;
		}

		case '3':
		{
			/* print list */
			groceries.printList();
			
			break;
		}

		case '4':
		{
			/* exit */
			cout << endl << "Bye bye! " << endl;
			delete temp;
			groceries.~List();
			break;
		}

		default:
		{
			/* input validation */
			cout << endl << "Error: please enter a number from 1 - 4 " 
					<< endl << endl;
			break;
		}
		}
	}

	return 0;

}
