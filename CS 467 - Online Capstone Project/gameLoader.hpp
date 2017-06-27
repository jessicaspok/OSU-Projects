#ifndef GAMELOADER_HPP
#define GAMELOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

#include "Room.h"
#include "Object.h"
#include "Character.h"
#include "Detective.h"
 
using namespace std;
using namespace cereal;

struct gamePkg{
	vector<shared_ptr<Character>> 	theChars;
	vector<shared_ptr<Object>>   	theObjs;
	vector<shared_ptr<Room>> 		theRooms;
	Detective 						thePlayer;
};


class gameLoadandSave{
  private:
	const string default_root="new_game";
	string currDIR;
	string pathName;
	
  public:
	gameLoadandSave();
	void setCurrDir(string );
	void generateGame(gamePkg*);
	void saveGame(gamePkg*, string);
	gamePkg *loadGame(vector<string>, vector<string>, vector<string>, string , string);
	gamePkg *loadNewGame(vector<string>, vector<string>, vector<string>, string );	
	void deleteGame(string );
	vector<string> getGameList();
	int addGameToList(string );
	int rmvGameFromList(string );

};

#endif