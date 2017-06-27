/*********************************************************************
** Program Filename: Item.cpp
** Author: Jessica Spokoyny
** Date: 01/29/15
** Description: Item class implementation file
** Input: string name, string units, int quantity, int unitPrice
** Output:
*********************************************************************/

#include "Item.h"

/*********************************************************************
** Function: constructor
** Description: creates an Item
** Parameters:  string name, string units, int quantity, double unit 
**	price
** Pre-Conditions: strings, int, and double are valid
** Post-Conditions:  Item object is created
*********************************************************************/
Item::Item(string a, string b, int c, double d)
{
	itemName = a;
	units = b;
	numberToBuy = c;
	unitPrice = d;
}

/* default constructor */
Item::Item() 
{
}

/*********************************************************************
** Function: setItemName
** Description: sets an Item's name
** Parameters:  string name
** Pre-Conditions: Item object exists, string is valid
** Post-Conditions:  itemName is set to the string passed
*********************************************************************/
void Item::setItemName(string a)
{
	itemName = a;
}

/*********************************************************************
** Function: setUnits
** Description: sets an Item's units
** Parameters:  string units
** Pre-Conditions: Item object exists, string is valid
** Post-Conditions:  units is set to the string passed
*********************************************************************/
void Item::setUnits(string b)
{
	units = b;
}

/*********************************************************************
** Function: setNumberToBuy
** Description: sets an Item's quantity
** Parameters:  int quantity
** Pre-Conditions: Item object exists, int is valid
** Post-Conditions:  numberToBuy is set to the int passed
*********************************************************************/
void Item::setNumberToBuy(int c)
{
	numberToBuy = c;
}

/*********************************************************************
** Function: setUnitPrice
** Description: sets an Item's unit price
** Parameters:  double unit price
** Pre-Conditions: Item object exists, double is valid
** Post-Conditions:  unitPrice is set to the double passed
*********************************************************************/
void Item::setUnitPrice(double d)
{
	unitPrice = d;
}
/*********************************************************************
** Function: getItemName
** Description: gets an Item's name
** Parameters:  none
** Pre-Conditions: Item object exists
** Post-Conditions:  string itemName is returned
*********************************************************************/
string Item::getItemName()
{
	return itemName;
}

/*********************************************************************
** Function: getUnits
** Description: gets an Item's units
** Parameters:  none
** Pre-Conditions: Item object exists
** Post-Conditions:  string units is returned
*********************************************************************/
string Item::getUnits()
{
	return units;
}

/*********************************************************************
** Function: getNumbertoBuy
** Description: gets an Item's quantity
** Parameters:  none
** Pre-Conditions: Item object exists
** Post-Conditions:  int numberToBuy is returned
*********************************************************************/
int Item::getNumberToBuy()
{
	return numberToBuy;
}

/*********************************************************************
** Function: getUnitPrice
** Description: gets an Item's unit price
** Parameters:  none
** Pre-Conditions: Item object exists
** Post-Conditions:  double unitPrice is returned
*********************************************************************/
double Item::getUnitPrice()
{
	return unitPrice;
}

/*********************************************************************
** Function: overloaded == operator
** Description: use == to compare item name and units
** Parameters:  an Item object
** Pre-Conditions: Item object is valid
** Post-Conditions:  true (if strings are the same) or false (if 
**	either string is different) is returned
*********************************************************************/
bool Item::operator==(Item& rhs)  
{
	return ((this->getItemName() == rhs.getItemName()) && (this->getUnits() == rhs.getUnits()));
}