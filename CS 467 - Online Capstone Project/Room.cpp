#include "Room.h"

Room::Room()
{
}

Room::Room(string n, string d, string s, string l, vector<shared_ptr<Object>> objects, vector<shared_ptr<Character>> people, int v)
{
	name = n;
	displayName = d;
	sd = s;
	ld = l;
	myObjects = objects;
	myPeople = people;
	visited = v;
}

void Room::enter()	
{
	cout << endl << "You are in " << displayName << "." << endl;

	if (visited == 0) {
		cout << ld << endl;
		visited++;
	}
	else {
		cout << sd << endl;
		visited++;
	}		  
}

void Room::setName(string oName)
{
	name = oName;
}

string Room::getName()
{
	return name;
}

string Room::getDisplayName()
{
	return displayName;
}

void Room::setLongDescription(string lDesc)
{
	ld = lDesc;
}

string Room::getLongDescription()
{
	return ld;
}

void Room::setShortDescription(string sDesc)
{
	sd = sDesc;
}

string Room::getShortDescription()
{
	return sd;
}

void Room::listObjects()
{
	int count;

	for (count = 0; count < myObjects.size(); count++) {
		if (myObjects[count]->hidden == false) {
			cout << " - " << myObjects[count]->displayName << endl;
		}
	}
}

void Room::listPeople()
{
	int count;
	int ppl = 0;
	for (count = 0; count < myPeople.size(); count++) {
		cout << " - " << myPeople[count]->displayName << endl;
		ppl++;
	}
	if (ppl == 0)
		cout << " - Looks like you're all alone in here.." << endl;
}

void Room::listTakeable()
{
	int count;
	int take = 0;
	for (count = 0; count < myObjects.size(); count++) {
		if (myObjects[count]->canTake == true && myObjects[count]->hidden == false) {
			cout << " - " << myObjects[count]->displayName << endl;
			take++;
		}
	}
	if (take == 0)
		cout << " - Sorry, you've gotta leave empty-handed.." << endl; 
}

bool Room::hasObject(string oName)	
{
	bool posess = false;
	int count;

	for (count = 0; count < myObjects.size(); count++) {
		if (oName == myObjects[count]->name) {
			posess = true;
			break;
		}
	}

	return posess;
}

void Room::removeObject(string oName)	
{
	if(hasObject(oName)){
		for (int i = 0; i < myObjects.size(); i++) {
		if (oName == myObjects[i]->name) {
			myObjects.erase(myObjects.begin() + i);
			}
		}	
	}
	return;
}

void Room::addObject(shared_ptr<Object> o){
	myObjects.push_back(o);
	return;
}

bool Room::hasPerson(string pName)	
{
	bool posess = false;
	int count;

	for (count = 0; count < myPeople.size(); count++) {
		if (pName == myPeople[count]->name) {
			posess = true;
			break;
		}
	}

	return posess;
}

void Room::removePerson(string pName)	
{
	if(hasPerson(pName)){
		for (int i = 0; i < myPeople.size(); i++) {
		if (pName == myPeople[i]->name) {
			myPeople.erase(myPeople.begin() + i);
			}
		}	
	}
	return;
}

void Room::addPerson(shared_ptr<Character> p){
	myPeople.push_back(p);
	return;
}

// first create all room objects then connect them with this function
void Room::addRoom(shared_ptr<Room> n, shared_ptr<Room> s, shared_ptr<Room> e, shared_ptr<Room> w)
{
	north = n;
	south = s;
	east = e;
	west = w;
}

shared_ptr<Room> Room::getRoom(string direction)
{
	if (direction == "north")
		return north;
	else if (direction == "south")
		return south;
	else if (direction == "east")
		return east;
	else if (direction == "west")
		return west;
}