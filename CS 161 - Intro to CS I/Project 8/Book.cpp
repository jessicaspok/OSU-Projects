/***************************************************************************
** Author: Jessica Spokoyny
** Date: August 15, 2015
** Description: This is the member function implementation section of the 
** class Book
***************************************************************************/

#include "Book.hpp"

// constructor
Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
	setLocation(ON_SHELF);
	setCheckedOutBy(NULL);
	setRequestedBy(NULL);
}

// get the check out length
int Book::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}

// get the idCode of the book
std::string Book::getIdCode()
{
	return idCode;
}

// get the title of the book
std::string Book::getTitle()
{
	return title;
}

// get the author of the book
std::string Book::getAuthor()
{
	return author;
}

// set the location of the book
void Book::setLocation(Locale l)
{
	location = l;
}

// get the location of the book
Locale Book::getLocation()
{
	return location;
}

// set the patron who checked out the book
void Book::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}

// get the patron who checked out the book
Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

// set the patron who requested the book
void Book::setRequestedBy(Patron* pc)
{
	requestedBy = pc;
}

// get the patron who requested the book
Patron* Book::getRequestedBy()
{
	return requestedBy;
}

// set the date the book was checked out
void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}

// get the date the book was checked out
int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

