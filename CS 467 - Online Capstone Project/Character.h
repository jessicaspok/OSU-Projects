#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "cereal/types/vector.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

using namespace std;
using namespace cereal;

class Character
{
public:
	string name;
	string displayName;
	string ld;
	int hasTalkedTo = 0;
	vector<string> dialogue;
	Character();
	Character(string, string, string, int, vector<string>);
	void setName(string);
	string getName();
	void setHasTalkedTo(int);
	int getHasTalkedTo();
	void setLongDescription(string);
	string getLongDescription();	
	void speak();
	
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
		  CEREAL_NVP(hasTalkedTo), 
		  CEREAL_NVP(dialogue)
		 );
	}
//ARCHIVE END
};

#endif