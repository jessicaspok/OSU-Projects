/*********************************************************************
** Program Filename: Queue.cpp
** Author: Jessica Spokoyny
** Date: 02/28/1602/12/2016
** Description: Queue implementation file
*********************************************************************/

#include "Queue.hpp"

/*********************************************************************
** Function: Constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: front and back point to NULL
*********************************************************************/
Queue::Queue()
{
	front = NULL;
	back = NULL;
}

/*********************************************************************
** Function: Destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: all nodes deleted and memory deallocated
*********************************************************************/
Queue::~Queue()
{
	/* point to first node */
	QueueNode *ptr = front;

	/* delete all nodes */
	while (ptr != NULL)
	{
		QueueNode *dlt = ptr;
		ptr = ptr->next;
		delete dlt;
	}
}

/*********************************************************************
** Function: add
** Description: adds item to back of queue
** Parameters: int
** Pre-Conditions: int is valid
** Post-Conditions: back points to the new node holding item passed
*********************************************************************/

void Queue::add(Creature *cr)
{
	// if the queue is empty
	if (front == NULL)
	{
		front = new QueueNode;
		front->data = cr;
		front->next = NULL;
		front->prev = NULL;
		back = front;
	}
	// if not empty, add a new node at the end
	else 
	{
		back->next = new QueueNode;
		back->next->data = cr;
		back->next->next = NULL;
		back->next->prev = back;
		back = back->next;
	}
}

/*********************************************************************
** Function: remove
** Description: removes and returns value in front of queue
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns value in front of queue, or 0 if empty
*********************************************************************/
void Queue::remove()
{
	Creature *toDel;
	QueueNode *node = front;

	// if only 1 node in queue
	if (front->next == NULL)
	{
		toDel = front->data;
		delete front;
		front = NULL;
		back = NULL;
	}
	// if more than 1 node in queue
	// remove the 1st node
	else
	{
		QueueNode *temp = node->next;
		toDel = front->data;
		delete front;
		front = temp;
		front->prev = NULL;
	}
}

/*********************************************************************
** Function: print
** Description: prints fighters who have scored points from most-least
** Parameters: none
** Pre-Conditions: the battle has ended
** Post-Conditions: results are printed to output
*********************************************************************/
void Queue::print()
{
	string firstType = " ";
	string firstName = " ";
	string secType = " ";
	string secName = " ";
	string thirdType = " ";
	string thirdName = " ";
	
	int firstPoints = 0;
	int secPoints = 0;
	int thirdPoints = 0;

	QueueNode *node = front;

	// for all of the fighters in the list
	while (node != NULL){

		// get the fighters points
		int temp = node->data->getPoints();

		// if the fighter has the most points
		if (temp >= firstPoints)
		{
			thirdType = secType;
			thirdName = secName;
			thirdPoints = secPoints;

			secType = firstType;
			secName = firstName;
			secPoints = firstPoints;

			firstType = node->data->getType();
			firstName = node->data->getName();
			firstPoints = temp;
		}
		// if the fighter has the second most points
		else if (temp >= secPoints)
		{
			thirdType = secType;
			thirdName = secName;
			thirdPoints = secPoints;

			secType = node->data->getType();
			secName = node->data->getName();
			secPoints = temp;
		}
		// if the fighter has the 3rd most points
		else if (temp >= thirdPoints)
		{
			thirdType = node->data->getType();
			thirdName = node->data->getName();
			thirdPoints = temp;
		}

		// get the next fighter
		node = node->next;
	}

	// print out the top 3 fighters that scored points
	if (firstPoints > 0)
		cout << " 1st: " << firstType << " " << firstName << " with " << firstPoints
		<< " points." << endl;

	if (secPoints > 0)
		cout << " 2nd: " << secType << " " << secName << " with " << secPoints
		<< " points." << endl;

	if (thirdPoints > 0)
		cout << " 3rd: " << thirdType << " " << thirdName << " with " << thirdPoints
		<< " points." << endl;

	cout << endl;
}


/* accessor function */
Queue::QueueNode * Queue::getFront()
{
	return front;
}