#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

#include "Object.h"
#include "Character.h"

using namespace std;
using namespace cereal;

class Room
{
public:
	string name;
	string displayName;
	string ld;
	string sd;
	int visited;
	vector<shared_ptr<Object>> myObjects;
	vector<shared_ptr<Character>> myPeople;
	Room();
	Room(string, string, string, string, vector<shared_ptr<Object>>, vector<shared_ptr<Character>>, int);
	void enter();
	void setName(string);
	string getName();
	string getDisplayName();
	void setLongDescription(string);
	string getLongDescription();
	void setShortDescription(string);
	string getShortDescription();
	void listObjects();
	void listPeople();
	void listTakeable();
	bool hasObject(string);
	void removeObject(string);
	void addObject(shared_ptr<Object> o);
	bool hasPerson(string);
	void removePerson(string);
	void addPerson(shared_ptr<Character> p);
	virtual void addRoom(shared_ptr<Room> n, shared_ptr<Room> s, shared_ptr<Room> e, shared_ptr<Room> w);
	virtual shared_ptr<Room> getRoom(string);

protected:
	shared_ptr<Room> north;
	shared_ptr<Room> south;
	shared_ptr<Room> east;
	shared_ptr<Room> west;     
	
//ARCHIVE BEGIN	
//Add variables to achive	
	friend class cereal::access;
	template <class Archive>
	void serialize( Archive &ar )
	{
	  ar( 
	      CEREAL_NVP(name),
		  CEREAL_NVP(displayName),
		  CEREAL_NVP(ld), 
		  CEREAL_NVP(sd),
		  CEREAL_NVP(visited),
		  CEREAL_NVP(myObjects),
		  CEREAL_NVP(myPeople),
		  CEREAL_NVP(north),
		  CEREAL_NVP(south),
		  CEREAL_NVP(east),
		  CEREAL_NVP(west)
		 );
	}
//ARCHIVE END

};
#endif