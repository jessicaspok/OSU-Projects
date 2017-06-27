#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "cereal/types/vector.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

using namespace std;
using namespace cereal;

class Object
{
public:
	string name;
	string displayName;
	string ld;
	vector<string> validVerbs;
	bool canTake;
	bool isLocked;
	bool insight;
	bool hidden;
	Object();
	Object(string, string, string, vector<string>, bool, bool, bool, bool);
	void setName(string);
	string getName();
	void setLongDescription(string);
	string getLongDescription();
	void setCanTake(bool b);
	bool getCanTake();
	void setIsLocked(bool b);
	bool getIsLocked();
	void setInsight(bool b);
	bool getInsight();
	void setHidden(bool b);
	bool getHidden();
	
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
		  CEREAL_NVP(validVerbs),
		  CEREAL_NVP(canTake),
		  CEREAL_NVP(isLocked),
		  CEREAL_NVP(insight),
		  CEREAL_NVP(hidden)
		 );
	}
//ARCHIVE END
};

#endif