/*********************************************************************
** Program Filename: List.cpp
** Author: Jessica Spokoyny
** Date: 01/29/15
** Description: List class implementation file
** Input: temp Item created in main
** Output: prints list, shows success failure of actions selected
*********************************************************************/

#include "List.h"
#include <array>
#include <iomanip>

/*********************************************************************
** Function: default constructor
** Description: creates new list of 4 Items
** Parameters:  none
** Pre-Conditions: none
** Post-Conditions:  List object is created, size of list is stored
**	in capacity variable
*********************************************************************/
List::List() 
{ 
	this->groceryList = new Item[4];
	this->capacity = (sizeof(groceryList) / sizeof(Item*));
}

/* destructor */
List::~List()
{
}
	
/*********************************************************************
** Function: addItem
** Description: adds an Item to the list
** Parameters:  temp Item
** Pre-Conditions: temp Item exists and is valid
** Post-Conditions:  Item is added to List or quantity is modified
*********************************************************************/
void List::addItem(Item &tmp)
{
	/* check if this name already exists in the list */
	/* if yes, ask to modify the quantity */
	for (int i = 0; i < itemCount; i++)
	{
		if (groceryList[i] == tmp)
		{
			char ans;

			cout << tmp.getItemName() << " already exists in your list." 
				<< " Would you like to update the quantity?" << endl;
			cout << "Enter Y for yes, or N to keep the quantity at " 
				<< groceryList[i].getNumberToBuy() << ": ";
			
			cin >> ans;
			cout << endl;

			if (ans == 'y' || ans == 'Y')
			{
				groceryList[i].setNumberToBuy(
						groceryList[i].getNumberToBuy() 
						+ tmp.getNumberToBuy());
				cout << "Ok, the quantity has been updated." << endl 
						<< endl;
			}
			else
			{
				cout << "Ok, the quantity has been left unchanged." 
						<< endl << endl;
			}
			
			return;
		}
	}
	
	/* check if the array is full */
	if (this->itemCount == this->capacity)
	{
		/* if yes, create a new array with one more space */
		Item* newList = new Item[capacity + 1];
		capacity++;
			
		/* copy everything from original list into new list */
		for (int i = 0; i < itemCount; i++)  
		{
			newList[i] = groceryList[i];
		}

		/* add new item to the next open space in the array */
		newList[capacity - 1] = Item(tmp.getItemName(), tmp.getUnits(), 
					tmp.getNumberToBuy(), tmp.getUnitPrice());

		/* increment number of items */
		itemCount++;
		
		/* reassign pointers so groceryList points to the correct place */
		Item* originalList = groceryList;
		this->groceryList = newList;

		delete [] originalList;
	}
	
	else
	{
		/* if not, just add item to next open space */
		groceryList[itemCount] = Item(tmp.getItemName(), tmp.getUnits(), 
					tmp.getNumberToBuy(), tmp.getUnitPrice());
		
		/* increment number of items */
		itemCount++;
	}

	return;
}

/*********************************************************************
** Function: removeItem
** Description: removes an Item from the list
** Parameters:  temp Item
** Pre-Conditions: temp Item exists and is valid
** Post-Conditions:  Item is removed from List if found
*********************************************************************/
void List::removeItem(Item &tmp)
{
	bool found = false;

	/* search for the item in the list */
	for (int j = 0; j < itemCount; j++)
	{
		if (groceryList[j] == tmp)
		{
			for (int k = j; k < (itemCount - 1); k++)
			{
				/* shift all elements after j over */
				groceryList[k] = groceryList[k + 1];
			}

			/* empty out the last space */
			groceryList[itemCount - 1] = Item();

			/* decrement number of items */
			itemCount--;

			found = true;

			cout << endl << "Ok, the item has been removed." << endl 
					<< endl;

			return;
		}
	}

	/* if item wasn't found, show error */
	if (!found)
	{
		cout << endl << "Error: that item isn't in your list. " << endl 
				<< endl;
	}
}

/*********************************************************************
** Function: getTotalPrice
** Description: calculates total price of list
** Parameters:  none
** Pre-Conditions: List exists and is valid
** Post-Conditions:  double total is returned
*********************************************************************/
double List::getTotalPrice()
{
	double total = 0;
	for (int k = 0; k < itemCount; k++)
	{
		total += (groceryList[k].getUnitPrice() * 
					groceryList[k].getNumberToBuy());
	}

	return total;
} 

/*********************************************************************
** Function: getCount
** Description: returns number of Items in the List
** Parameters:  none
** Pre-Conditions: List exists and is valid
** Post-Conditions:  int itemCount is returned
*********************************************************************/
int List::getCount()
{
	return itemCount;
}

/*********************************************************************
** Function: printList
** Description: displays the list
** Parameters:  none
** Pre-Conditions: List exists and is valid
** Post-Conditions:  Output shows contents of list
*********************************************************************/
void List::printList()
{
	/* print list header */
	cout << endl << "Grocery List: " << endl << endl;
	cout << fixed << showpoint << setprecision(2);
	
	/* print column headers */
	cout << setw(15) << "NAME" << setw(15) << "UNITS" << setw(15) 
			<< "QUANTITY" << setw(15) << "UNIT PRICE" << setw(15) << 
			"EXT. PRICE" << endl << endl;
	
	/* loop through each Item and print info */
	for (int l = 0; l < itemCount; l++)
	{
		cout << setw(15) << groceryList[l].getItemName() << setw(15) << 
			groceryList[l].getUnits() << setw(15) << 
			groceryList[l].getNumberToBuy() << setw(15) << 
			groceryList[l].getUnitPrice() << setw(15) <<
			(groceryList[l].getUnitPrice() * 
			groceryList[l].getNumberToBuy()) << endl;
	}

	/* print grand total */
	cout << endl << endl << setw(60) << "GRAND TOTAL: $" << setw(15) 
			<< getTotalPrice() << endl << endl;
}
