#include "Detective.h"

Detective::Detective()
{
	name = "Detective";
	arrestCount = 0;
	drinkCount = 0;
	bunkVisited = false;
	hiddenVisited = false;
}

void Detective::setCurrentRoom(shared_ptr<Room> room)
{
	currentRoom = room;
}
	
shared_ptr<Room> Detective::getCurrentRoom()
{
	return currentRoom;
}

void Detective::setCurRoomStr(string s) {
	currentRoom->name = s;
}

string Detective::getCurRoomStr() {
	return curRoomStr;
}

void Detective::setPrevRoom(shared_ptr<Room> room)
{
	prevRoom = room;
}
	
shared_ptr<Room> Detective::getPrevRoom()
{
	return prevRoom;
}

void Detective::setPrevRoomStr(string s) {
	prevRoom->name = s;
}

string Detective::getPrevRoomStr() {
	return prevRoomStr;
}

bool Detective::isInInventory(string s){
	for (int i = 0; i < this->myObjects.size(); i++){
		if (this->myObjects[i]->getName() == s){
			return true;
		}
	}
	return false;
}

shared_ptr<Object> Detective::getFromInventory(string s){
	for (int i = 0; i < this->myObjects.size(); i++){
		if (this->myObjects[i]->getName() == s){
			return this->myObjects[i];
		}
	}
	return static_cast<shared_ptr<Object>>(nullptr);
}



int Detective::addToInventory(shared_ptr<Object> o)
{
	int taken = 0;
	if (o->canTake == true) {
		myObjects.push_back(o);
		taken = 1;
	}
	else
		cout << "Sorry, this couldn't be added to your inventory.." << endl;
		
		return taken;
}

void Detective::removeFromInventory(shared_ptr<Object> o){
	for (int i = 0; i < myObjects.size(); i++){
		if (myObjects[i] == o){
			myObjects.erase(myObjects.begin() + i);
		}
	}
}

void Detective::listInventory()
{
	for (int i = 0; i < myObjects.size(); i++) {
		cout << myObjects[i]->displayName << endl; 
	}
}

void Detective::addToSuspects(string cName)
{
	int match = 0, invalid = 0;

	for (int i = 0; i < suspects.size(); i++){
		if (suspects[i] == cName){
			cout << "This person is already on your suspect list..";
			match = 1;
		}
	}
	
	if (match == 0 && invalid == 0) {
			suspects.push_back(cName);
			cout << cName << " has been successfully added to your suspect list.\n";
		}
}

void Detective::removeFromSuspects(string cName)
{
	for (int i = 0; i < suspects.size(); i++){
		if(suspects[i] == cName){
			suspects.erase(suspects.begin() + i);
		}
	}
}

void Detective::listSuspects()
{
	cout << "\nSuspect List: ";
	for (int i = 0; i < suspects.size(); i++) {
		if (i < suspects.size() - 1)
			cout << suspects[i] << ", ";
		else
			cout << suspects[i] << endl;
	}
}

int Detective::getArrestCount()
{
	return arrestCount;
}

void Detective::setArrestCount(int a)
{
	arrestCount = a;
}

int Detective::getDrinkCount()
{
	return drinkCount;
}

void Detective::setDrinkCount(int d)
{
	drinkCount = d;
}

bool Detective::getBunkVisited()
{
	return bunkVisited;
}

void Detective::setBunkVisited(bool b)
{
	bunkVisited = b;
}

bool Detective::getHiddenVisited() 
{
	return hiddenVisited;
}

void Detective::setHiddenVisited(bool h)
{
	hiddenVisited = h;
}
