/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Jessica Spokoyny
 * Date: 05/27/2016
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int i;
    int r = 0;
    for (i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int i;
    int r = 0;
    for (i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link);
    link = NULL;
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    int i;
    for (i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    assert(map != NULL);
	int i;

	// loop through each bucket
	for (i = 0; i < map->capacity; i++) {
            if (map->table[i] == NULL)
                continue;

        HashLink *current = map->table[i];;
        HashLink *next = NULL;

        // free until no links remain in the bucket
        do
        {
            next = current->next;
            hashLinkDelete(current);
            current = next;
        } while (next != NULL);

        hashLinkDelete(next);

        map->table[i] = NULL;
	}

	free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    assert(map != NULL);

    // int to store the hashed key
	int hashIndex = HASH_FUNCTION(key);
	hashIndex = (int)hashIndex % map->capacity;

    // iterator to search all links
	struct HashLink* current = map->table[hashIndex];

	while (current != NULL) {
		if (strcmp(current->key, key) == 0)
			return &current->value;
		current = current->next;
	}

	// value not found
	return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    assert(map != NULL);

    // iterator
	struct HashLink* current = NULL;
	int i;

	// new larger hashMap
	struct HashMap* tempHashMap = hashMapNew(capacity);
	assert(tempHashMap != NULL);

	// iterate and rehash into new hashMap
	for (i = 0; i < map->capacity; i++) {
		current = map->table[i];
		while (current != NULL) {
			hashMapPut(tempHashMap, current->key, current->value);
			current = current->next;
		}
	}

	// reassign pointers
	map->table = tempHashMap->table;
	map->capacity = tempHashMap->capacity;

	free(tempHashMap);
	tempHashMap = NULL;
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // int to store the hashed key
	int hashIndex = HASH_FUNCTION(key);
	hashIndex = (int)hashIndex % map->capacity;

	// create new link
	HashLink *newLink = (struct HashLink *)malloc(sizeof(HashLink));
	assert(newLink != NULL);

    // if the table already contains this key remove it
	if (hashMapContainsKey(map, key))
        hashMapRemove(map, key);

    // set key/value of new link
	newLink->key = key;
	newLink->value = value;

	// assign newLink->next to current pointer at hashIndex (or NULL)
	newLink->next = map->table[hashIndex];

	map->table[hashIndex] = newLink;

	map->size++;

	// resize if necessary
	if ((map->size / (double)map->capacity) >= MAX_TABLE_LOAD)
		resizeTable(map, map->capacity * 2);
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    assert(map != NULL);

    // int to store the hashed key
	int hashIndex = HASH_FUNCTION(key);
	hashIndex = (int)hashIndex % map->capacity;

	struct HashLink * current = map->table[hashIndex];
	struct HashLink * previous = NULL;

	// current is empty (key not found)
	if (current == NULL)
		return;

	 // iterate over links until key found or end of chain reached(key not found)
	while (current != NULL && (strcmp(current->key, key) != 0)) {
		previous = current;
		current = current->next;
	}

	// first link contains key
	if ((strcmp(current->key, key) == 0) && previous == NULL) {
		map->table[hashIndex] = current->next;
		hashLinkDelete(current);
		map->size--;
	}

	// other link contains key
	else if (strcmp(current->key, key) == 0) {
		previous->next = current->next;
		hashLinkDelete(current);
		map->size--;
	}

	// end of map is reached without finding key
	else if (current == NULL)
		return;
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // int to store the hashed key
	int hashIndex = HASH_FUNCTION(key);
	hashIndex = (int)hashIndex % map->capacity;

	struct HashLink * current = map->table[hashIndex];

	// if current bucket is not empty
	if (current != NULL)
    {
		// first link contains key
		if (!(strcmp(current->key, key)))
            return 1;

        // iterate through links comparing keys
    	while(current->next != NULL)
    	{
    		current = current->next;
    		if (!(strcmp(current->key, key)))
                return 1;
    	}
	}

	// key not found
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    int count = 0;
	int i;

	// search map for empty buckets
	for (i = 0; i < map->capacity; i++)
	{
		if (map->table[i] == NULL)
			count++;
	}

	return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    float load;
	float size = (float)map->size;
	float cap = (float)map->capacity;
	load = size / cap;
    return load;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    int i;
    for (i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
