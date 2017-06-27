#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

#include "Character.h"
#include "Object.h"
#include "Room.h"

using namespace std;
using namespace cereal;

class Detective	: public Character
{
public:	
	Detective();
	int arrestCount;
	int drinkCount;
	bool bunkVisited;
	bool hiddenVisited;
	bool isInInventory(string s);
	int addToInventory(shared_ptr<Object> o);
	void removeFromInventory(shared_ptr<Object> o);	
	void listInventory();
	void addToSuspects(string);
	void removeFromSuspects(string);	
	void listSuspects();
	void setCurrentRoom(shared_ptr<Room> r);
	shared_ptr<Room> getCurrentRoom();
	void setCurRoomStr(string);
	string getCurRoomStr();
	void setPrevRoom(shared_ptr<Room> r);
	shared_ptr<Room> getPrevRoom();
	void setPrevRoomStr(string);
	string getPrevRoomStr();
	vector<shared_ptr<Object>> myObjects;
	vector<string> suspects;
	shared_ptr<Room> currentRoom;
	shared_ptr<Room> prevRoom;
	string curRoomStr;
	string prevRoomStr;
	int getArrestCount();
	void setArrestCount(int);
	int getDrinkCount();
	void setDrinkCount(int);
	bool getBunkVisited();
	void setBunkVisited(bool);
	bool getHiddenVisited();
	void setHiddenVisited(bool);
	shared_ptr<Object> getFromInventory(string s);

	
//ARCHIVE BEGIN	
//Add variables to achive	
	friend class cereal::access;
	template <class Archive>
	void serialize( Archive &ar )
	{
	  ar( 
	      CEREAL_NVP(myObjects), 
		  CEREAL_NVP(suspects),
		  CEREAL_NVP(currentRoom),
		  CEREAL_NVP(prevRoom),
		  CEREAL_NVP(arrestCount), 
		  CEREAL_NVP(drinkCount),
		  CEREAL_NVP(bunkVisited),
		  CEREAL_NVP(hiddenVisited)
		 );
	}
//ARCHIVE END
};

#endif