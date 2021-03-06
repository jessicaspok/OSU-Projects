#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	assert(list != 0);

	// allocate sentinels
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel);

    // assign sentinels next and prev
    list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->next = 0;

	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
    assert(link != 0);

	if (list->frontSentinel != list->backSentinel)
    {
		// allocate new link
		struct Link * newLink = malloc(sizeof(struct Link));
        assert(list->frontSentinel != 0);

        // set value of new link
        newLink->value = value;

		// set pointers
		link->prev->next = newLink;
		newLink->prev = link->prev;
		link->prev = newLink;
		newLink->next = link;
	}

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != 0);
    assert(link != 0);

	if (list->frontSentinel != list->backSentinel){
		// set pointers
		link->next->prev = link->prev;
		link->prev->next = link->next;

        free(link);
	}

	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != 0);
    assert(list->size > 0);

	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != 0);
    assert(!linkedListIsEmpty(list));

	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != 0);
    assert(!linkedListIsEmpty(list));

    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != 0);
    assert(!linkedListIsEmpty(list));

    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != 0);

	return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != 0);

    // create pointer to traverse list
    struct Link * temp;
    temp = list->frontSentinel->next;

    // print value and move on to next link
	while(temp->next != list->backSentinel){
        printf("%i \n", temp->value);
        temp = temp->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != 0);

    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
    assert(!linkedListIsEmpty(list));

    // create pointer to traverse list
    struct Link * temp;
    temp = list->frontSentinel->next;

    // check if value passed matches current link's value and move on to next link
	while(temp->next != list->backSentinel){
		// value found
		if(temp->value == value)
		{
		    return 1;
		}
		temp = temp->next;
	}

	// value not found
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
    assert(!linkedListIsEmpty(list));

    // create pointer to traverse list
    struct Link * temp;
    temp = list->frontSentinel->next;

    // check if value passed matches current link's value and move on to next link
	while(temp != list->backSentinel){
		// value found
		if(temp->value == value)
        {
            removeLink(list, temp);
        }
        temp = temp->next;
    }
}
