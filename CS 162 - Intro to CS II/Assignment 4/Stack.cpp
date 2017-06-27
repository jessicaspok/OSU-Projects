/****************************************************************************************
** Class file: Stack.cpp
** Author: Jessica Spokoyny
** Date: 02/28/162-28-16
** Description: Creates a simple integer Stack where a user can add and remove values
**              to and from the stack.
****************************************************************************************/

#include "Stack.hpp"

/*********************************************************************
** Function: Constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: top points to NULL
*********************************************************************/
Stack::Stack()
{
	top = NULL;
}

/*********************************************************************
** Function: Destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: all nodes deleted and memory deallocated
*********************************************************************/
Stack::~Stack()
{
	/* point to first node */
	StackNode *ptr = top;

	/* delete all nodes */
	while (ptr != NULL)
	{
		StackNode *dlt = ptr;
		ptr = ptr->next;
		delete dlt;
	}
}

/*********************************************************************
** Function: add()
** Description: adds item to top of stack
** Parameters: int
** Pre-Conditions: int is valid
** Post-Conditions: top points to the new node holding item passed
*********************************************************************/
void Stack::add(Creature *cr)
{
	// if the stack is empty
	if (top == NULL)
	{
		top = new StackNode;
		top->data = cr;
		top->next = NULL;
	}

	// if not, add the new node at the end of the list
	else 
	{
		StackNode *node = top;

		while (node->next != NULL)
		{
			node = node->next;
		}

		node->next = new StackNode;
		node->next->data = cr;
		node->next->next = NULL;

	}
}

/*********************************************************************
** Function: remove()
** Description: removes and returns value in top of stack
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns value in top of stack
*********************************************************************/
void Stack::remove()
{
	Creature *toDel;                             
	StackNode *prevNode = top;
	StackNode *node = top;

	// if theres only one node in the stack
	if (top->next == NULL)
	{
		toDel = top->data;
		delete top;
		top = NULL;
	}

	// find the last node and delete that one
	else{
		// at the last node?
		while (node->next != NULL)
		{
			prevNode = node;
			node = node->next;
		}

		// capture deleted value and delete the node
		toDel = node->data;
		delete node;

		// set the newly last node's next ptr to NULL
		prevNode->next = NULL;
	}
}

/*********************************************************************
** Function: print
** Description: prints fighters who have died in order they were  
**	killed
** Parameters: none
** Pre-Conditions: the battle has ended
** Post-Conditions: results are printed to output
*********************************************************************/
void Stack::print()
{
	cout << endl << "Defeated Fighters: " << endl << endl;
	 
	StackNode *node = top;
	while (node != NULL)
	{
		cout << " " << node->data->getType() << " "
			<< node->data->getName() << endl;

		node = node->next;
	}

	cout << endl;
}
