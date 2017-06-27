/***************************************************************************
** Author: Jessica Spokoyny
** Date: August 15, 2015
** Description: This is the member function implementation section of the 
** class Patron
***************************************************************************/

#include "Patron.hpp"

// constructor 
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0.0;
}

// get the Patron's idNum
std::string Patron::getIdNum()
{
	return idNum;
}

// get the Patron's  name
std::string Patron::getName()
{
	return name;
}

// add the Book to checkedOutBooks
void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

// remove the Book from checkedOutBooks
void Patron::removeBook(Book* b)
{
	for (unsigned int i = 0; i < checkedOutBooks.size(); i++)
	{
		if (checkedOutBooks.at(i) == b)
		{
			checkedOutBooks.erase(checkedOutBooks.begin() + i);
		}
	}
}

// get the vector containing the Books a Patron has checked out
std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

// a positive amount increases the fineAmount, a negative one decreases it
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}

// get the fine amount owed by the Patron
double Patron::getFineAmount()
{
	return fineAmount;
}

