/***************************************************************************
** Author: Jessica Spokoyny
** Date: August 15, 2015
** Description: This is the member function implementation section of the 
** class Library
***************************************************************************/

#include "Library.hpp"

// default constructor
Library::Library()
{
	currentDate = 0;
}

// add a book to holdings 
void Library::addBook(Book* b)
{
	holdings.push_back(b);
}


// add a patron to members
void Library::addPatron(Patron* p)
{
	members.push_back(p);
}

// return a pointer to the book corresponding to the ID parameter 
// or NULL if no such book is in holdings
Book* Library::getBook(std::string bID)
{
	for (unsigned int i = 0; i < holdings.size(); i++)
	{
		if (holdings.at(i)->getIdCode() == bID)
		{
			return holdings.at(i);
		}
	}
	
	return NULL;
}

// return a pointer to the patron corresponding to the ID parameter 
// or NULL if no such patron is in members
Patron* Library::getPatron(std::string pID)
{
	for (unsigned int i = 0; i < members.size(); i++)
	{
		if (members.at(i)->getIdNum() == pID)
		{
			return members.at(i);
		}
	}

	return NULL;
}

/**********************************
CHECKOUT BOOK
The function used to check out a book
***********************************/

std::string Library::checkOutBook(std::string pID, std::string bID)
{
	Book* b = getBook(bID);
	Patron* p = getPatron(pID);

	bool pExist = false, bExist = false;

	// check whether the book exists
	for (unsigned int i = 0; i<holdings.size(); i++)
	{
		// book exists
		if (bID == holdings.at(i)->getIdCode())
		{
			b = holdings.at(i);
			bExist = true;
			break;
		}
	}

	// book doesn't exist 
	if (bExist == false)
	{
		return "book not found";
	}

	// check whether the patron exists
	for (unsigned int i = 0; i<members.size(); i++)
	{
		// patron exists
		if (pID == members.at(i)->getIdNum())
		{
			p = members.at(i);
			pExist = true;
			break;
		}
	}

	// patron doesn't exist
	if (pExist == false)	
	{
		return "patron not found";
	}

	// book is already checked out
	if (b->getLocation() == CHECKED_OUT)
	{
		return "book already checked out";
	}

	// book is on hold by another patron
	else if (b->getLocation() == ON_HOLD_SHELF && b->getRequestedBy() != p)
	{
		return "book on hold by other patron";
	}

	// check out the book if conditions are met
	else
	{
		b->setCheckedOutBy(p);
		b->setDateCheckedOut(currentDate);
		b->setLocation(CHECKED_OUT);
		b->setRequestedBy(NULL);
		p->addBook(b);

		return "check out successful";
	}
}

/**********************************
RETURN BOOK
The function used to return a book
***********************************/

std::string Library::returnBook(std::string bID)
{
	Book* b = getBook(bID);
	bool bExist = false;

	// check whether the book exists
	for (unsigned int i = 0; i < holdings.size(); i++)
	{
		// book exists
		if (holdings.at(i)->getIdCode() == bID)
		{
			b = holdings.at(i);
			bExist = true;
			break;
		}
	}

	// book doesn't exist
	if (bExist == false)
	{
		return "book not found";
	}
	
	// book has not been checked out
	if (b->getLocation() != CHECKED_OUT)
	{
		return "book already in library";
	}

	// book has been checked out
	else if (b->getLocation() == CHECKED_OUT)
	{
		// book has been requested by a patron
		if (b->getRequestedBy() != NULL)
		{
			Patron* p = b->getCheckedOutBy();
			p->removeBook(b);
			b->setLocation(ON_HOLD_SHELF);
			b->setCheckedOutBy(NULL);
			
return "return successful";
		}

		// book has not been requested by a patron
		else
		{
			Patron* p = b->getCheckedOutBy();
			p->removeBook(b);
			b->setLocation(ON_SHELF);
			b->setCheckedOutBy(NULL);
			
			return "return successful";
		}
	}
}
		
/**********************************
Request Book
the function used to request a book
***********************************/

std::string Library::requestBook(std::string pID, std::string bID)
{
	Book* b = getBook(bID);
	Patron* p = getPatron(pID);
	bool pExist = false, bExist = false;

	// check whether the book exists
	for (unsigned int i = 0; i < holdings.size(); i++)
	{
		// book exists
		if (holdings.at(i)->getIdCode() == bID)
		{
			b = holdings.at(i);
			bExist = true;
			break;
		}
	}

	// book doesn't exist
	if (bExist == false)	
	{
		return "book not found";
	}

	// check whether the patron exists
	for (unsigned int i = 0; i < members.size(); i++)
	{
		// patron exists
		if (members.at(i)->getIdNum() == pID)
		{
			p = members.at(i);
			pExist = true;
			break;
		}
	}

	// patron doesn't exist
	if (pExist = false) 
	{
		return "patron not found";
	}

	// book is on shelf
	if (b->getLocation() == ON_SHELF)
	{
		b->setRequestedBy(p);
		b->setLocation(ON_HOLD_SHELF);
		
		return "request successful";
	}

	// book is checked out 
	else if (b->getLocation() == CHECKED_OUT) 
	{
		if (b->getRequestedBy() == NULL)
		{
			b->setRequestedBy(p);
			
			return "request successful";
		}

		// book is checked out and a patron has already requested it
		if (b->getRequestedBy() != NULL)
		{
			return "book on hold by other patron";
		}
	}

	// book is already on hold 
	else if (b->getLocation() == ON_HOLD_SHELF)	
	{
		return "book on hold by other patron";
	}
}

/****************************
PAY FINE
This function lets a patron 
add money to his/her account 
and deducts that payment from 
their total fine amount
*****************************/

std::string Library::payFine(std::string pID, double payment)
{
	Patron* p = getPatron(pID);
	bool pExist = false;

	// make payment negative to subtract from fines owed
	payment *= -1;

	// check whether the patron exists
	for (unsigned int i = 0; i < members.size(); i++)
	{
		// patron exists
		if (members.at(i)->getIdNum() == pID)
		{
			p = members.at(i);
			pExist = true;
			break;
		}
	}

	// patron doesn't exist
	if (pExist == false)  
	{
		return "patron not found";
	}

	// change the patron's fine amount by the payment amount
	for (unsigned int i = 0; i < members.size(); i++)
	{
		if (members.at(i)->getIdNum() == pID)
		{
			p->amendFine(payment);

			return "payment successful";
		}
	}
}


/*****************************************
Increment Date Function 
This function increments the date and
increases each patron's fines by 10 cents 
for each overdue book they have checked out
*****************************************/

void Library::incrementCurrentDate()
{
	Patron* p;	
	Book* b;

	// increment the date by 1 each time this function is called
	currentDate++;	

	// loop through all checked out books by all patrons
	for (unsigned int i = 0; i < members.size(); i++)
	{
		p = members.at(i);

		// the patron has book(s) checked out
		if (p->getCheckedOutBooks().empty() == false)
		{
			// loop through each book that the patron has checked out
			for (unsigned int j = 0; j<(p->getCheckedOutBooks().size()); j++)
			{
				b = p->getCheckedOutBooks().at(j);

				// the book has been checked out for more than 21 days
				int length = (currentDate - (b->getDateCheckedOut()));
				if (length > Book::CHECK_OUT_LENGTH)
				{
					// add a fine of .10 for every day overdue
					members.at(i)->amendFine(0.10);	

				}
			}
		}
	}
}


