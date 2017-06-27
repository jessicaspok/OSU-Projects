#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	assert(list != 0);

	// set size to 0
	list->size = 0;

	// allocate sentinel
	list->sentinel = (struct Link*) malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	// assign sentinels next and prev
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// allocate link
	struct Link* newLink = (struct Link*) malloc(sizeof(struct Link));
	assert(newLink != 0);

	// set value
	newLink->value = value;

	// set pointers
	newLink->next = 0;
	newLink->prev = 0;

	return(newLink);
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
	assert(link != 0);

	// create new link
	struct Link* newLink = createLink(value);

    // set value
	newLink->value = value;

	// set pointers
	newLink->next = link->next;
	newLink->prev = link;
	link->next->prev = newLink;
	link->next = newLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list!=0);
	assert(!circularListIsEmpty(list));

	// set pointers
	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// create pointers to traverse list
	struct Link* iter = list->sentinel;
	struct Link* temp = iter;

	iter->prev->next = 0;

    // remove links and free them
	while (temp != 0)
    {
        iter = iter->next;
        temp->next = temp->prev = 0;
        free (temp);
        temp = iter;
    }

    list->size = 0;
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != 0);
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != 0);

	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	return(list->sentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	return(list->sentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != 0);

	// empty
	if(list->size == 0)
	{
		return(1);
	}

	// not empty
	return(0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	// create pointer to traverse list
	struct Link* temp = list->sentinel->next;

	// print value and move on to the next (until sentinel is reached)
	while (temp != list->sentinel)
	{
		printf("%g \n", temp->value);
		temp = temp->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));

	// create temporary pointers to access links
	struct Link* tempA;
	struct Link* tempB;

	// swap sentinel pointers
	tempA = list->sentinel->next;
	list->sentinel->next = list->sentinel->prev;
	list->sentinel->prev = tempA;

    // move on to next link
	tempA = list->sentinel->next;
	tempB = list->sentinel->next;

	int i;
	for(i = 0; i < list->size; i++)
	{
		// swap pointers
		tempA->next = tempA->prev;
		tempA->prev = tempB->next;

        // move on to next link
		tempA = tempA->next;
		tempB = tempA->next;
	}
}
