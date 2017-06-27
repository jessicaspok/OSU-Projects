#include "Character.h"

Character::Character()
{
}

Character::Character(string cName, string dName, string desc, int t, vector<string> d)
{
	name = cName;
	displayName = dName;
	ld = desc;
	hasTalkedTo = 0;
	dialogue = d;
}

void Character::setName(string pName)
{
	name = pName;
}

string Character::getName()
{
	return name;
}


void Character::setHasTalkedTo(int t)
{
	this->hasTalkedTo = t;
}

int Character::getHasTalkedTo()
{
	return this->hasTalkedTo;
}

void Character::setLongDescription(string desc)
{
	ld = desc;
}

string Character::getLongDescription()
{
	return ld;
}

void Character::speak(){
	int temp = this->getHasTalkedTo();
	cout << this->dialogue[temp] << endl;	
	if(temp < 1){
		this->setHasTalkedTo(1);
		}
}