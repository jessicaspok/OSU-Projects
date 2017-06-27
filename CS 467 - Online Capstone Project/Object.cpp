#include "Object.h"

Object::Object()
{
}

Object::Object(string myName, string dispName, string longDesc, vector<string> vVerbs, bool takeable, bool locked, bool ins, bool hid)
{
	name = myName;
	displayName = dispName;
	ld = longDesc;
	validVerbs = vVerbs;
	canTake = takeable;
	isLocked = locked;
	insight = ins;
	hidden = hid;
}

void Object::setName(string oName)
{
	name = oName;
}

string Object::getName()
{
	return name;
}

void Object::setLongDescription(string lDesc)
{
	ld = lDesc;
}

string Object::getLongDescription()
{
	return ld;
}

void Object::setCanTake(bool b)
{
	canTake = b;
}

bool Object::getCanTake()
{
	return canTake;
}

void Object::setIsLocked(bool l)
{
	isLocked = l;
}

bool Object::getIsLocked()
{
	return isLocked;
}

void Object::setInsight(bool b)
{
	insight = b;
}

bool Object::getInsight()
{
	return insight;
}

void Object::setHidden(bool h)
{
	hidden = h;
}

bool Object::getHidden()
{
	return hidden;
}