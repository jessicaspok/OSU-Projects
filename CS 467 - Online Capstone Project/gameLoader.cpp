#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

#include "Room.h"
#include "gameLoader.hpp" 

using namespace std;
using namespace cereal;

#define DEBUG 0
#define DEBUG_PRINT_LN if(DEBUG)

gameLoadandSave::gameLoadandSave(){
	    currDIR = default_root;
 
}
	
void gameLoadandSave::setCurrDir(string dir){
	
		const int dir_err = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == dir_err)
		{
			//printf("Error creating directory!");
			//exit(1);
		}	
	currDIR ="./" + dir + "/";		
}


void gameLoadandSave::generateGame(gamePkg *bundle){
	
	addGameToList("new_game");
	saveGame(bundle, default_root);
}


//Save all rooms, characters and objects to their respective folders
void gameLoadandSave::saveGame(gamePkg *bundle, string filename){
	vector<shared_ptr<Room>>  	  listRoom = bundle->theRooms;
	vector<shared_ptr<Character>> listChar = bundle->theChars;
	vector<shared_ptr<Object>>    listObjs = bundle->theObjs;
	Detective 		  			  player   = bundle->thePlayer;
	
	setCurrDir(filename);
	setCurrDir(filename + "/" + "Rooms");
	for(int i=0; i < listRoom.size(); i++){
		shared_ptr<Room> room = listRoom[i];
		pathName = currDIR + room->getName() + ".json";
		 
        ofstream outputjsonFile(pathName, std::ios::out);
        JSONOutputArchive archive_out( outputjsonFile );
	
		archive_out( CEREAL_NVP(room));
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}	
	
	setCurrDir(filename + "/" + "Characters");
	for(int i=0; i < listChar.size(); i++){
		shared_ptr<Character> characters = listChar[i];
		pathName = currDIR + characters->getName() + ".json";
		 
        ofstream outputjsonFile(pathName, std::ios::out);
        JSONOutputArchive archive_out( outputjsonFile );
	
		archive_out( CEREAL_NVP(characters));
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}
	
	setCurrDir(filename + "/" +  "Objects");
	for(int i=0; i < listObjs.size(); i++){
		shared_ptr<Object> objs = listObjs[i];
		pathName = currDIR + objs->getName() + ".json";
		 
        ofstream outputjsonFile(pathName, std::ios::out);
        JSONOutputArchive archive_out( outputjsonFile );
	
		archive_out( CEREAL_NVP(objs));
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}
	
	setCurrDir(filename + "/" + "Player");
		Detective detective = player;
		pathName = currDIR + "detective.json";
		 
        ofstream outputjsonFile(pathName, std::ios::out);
        JSONOutputArchive archive_out( outputjsonFile );
	
		archive_out( CEREAL_NVP(detective));
		DEBUG_PRINT_LN cout<<"file "<<" is -> "<<pathName<<endl;
		
}


gamePkg *gameLoadandSave::loadNewGame(vector<string> rmName, vector<string> chrName, vector<string> obName, string player){
	DEBUG_PRINT_LN cout<<"Loading new game..."<<pathName<<endl;
	return loadGame(rmName, chrName, obName, player, default_root);
}

gamePkg *gameLoadandSave::loadGame(vector<string> rmName, vector<string> chrName, vector<string> obName, string player, string filename){
	vector<shared_ptr<Room>> 		listRoom;
	vector<shared_ptr<Character>> 	listCharacter;
	vector<shared_ptr<Object>>		listObject;

	setCurrDir(filename);
	setCurrDir(filename + "/" + "Rooms");
	for(int i=0; i < rmName.size(); i++){
		pathName = currDIR + rmName[i] + ".json";
		
		shared_ptr<Room> room;
		
        ifstream inputjsonFile(pathName);
        JSONInputArchive archive_in( inputjsonFile );
	
		archive_in( cereal::make_nvp("room",room));
		listRoom.push_back(room);
		
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}	

	setCurrDir(filename + "/" + "Characters");
	for(int i=0; i < chrName.size(); i++){
		pathName = currDIR + chrName[i] + ".json";
		
		shared_ptr<Character> characters;
		
        ifstream inputjsonFile(pathName);
        JSONInputArchive archive_in( inputjsonFile );
	
		archive_in( cereal::make_nvp("characters",characters));
		listCharacter.push_back(characters);
		
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}

	setCurrDir(filename + "/" + "Objects");
	for(int i=0; i < obName.size(); i++){
		pathName = currDIR + obName[i] + ".json";

		shared_ptr<Object> objs;
		
        ifstream inputjsonFile(pathName);
        JSONInputArchive archive_in( inputjsonFile );
	
		archive_in( cereal::make_nvp("objs",objs));
		listObject.push_back(objs);
		
		DEBUG_PRINT_LN cout<<"file "<<i<<" is -> "<<pathName<<endl;
	}
	
	setCurrDir(filename + "/" + "Player");
		pathName = currDIR + "detective.json";
		 
		Detective detective;
		
        ifstream inputjsonFile(pathName);
        JSONInputArchive archive_in( inputjsonFile );
	
		archive_in( cereal::make_nvp("detective", detective));
		
		DEBUG_PRINT_LN cout<<"file "<<" is -> "<<pathName<<endl;
	
	gamePkg *mybundle = new gamePkg();
		mybundle->theChars 	= listCharacter;
		mybundle->theObjs	= listObject;
		mybundle->theRooms	= listRoom;
		mybundle->thePlayer	= detective;	

  return mybundle;
}

void gameLoadandSave::deleteGame(string filename){
//use the system functions to delete given filename/dir
//from current pathName and update the games list to 
//reflect this change.

#define BLAST "rm -R -f  \""

string command = BLAST + filename + "\"";

	system(command.c_str());
	
	rmvGameFromList(filename);
}	

vector<string> gameLoadandSave::getGameList(){

		pathName = "./savedGames.json";
		 
		vector<string> savedGames;
		
        ifstream inputjsonFile(pathName);
        JSONInputArchive archive_in( inputjsonFile );
	
		archive_in( cereal::make_nvp("savedGames", savedGames));
		
		return savedGames;		
}
	
	
int gameLoadandSave::addGameToList(string filename){
vector<string> savedGames;
		string response;
		
	savedGames = getGameList();

	for(int i = 0; i < savedGames.size(); i++){
		if (savedGames[i] == filename){
			  cout<<"file "<<filename<<" exists. Overwrite? [Y/N]"<<endl;
			  getline (cin, response);
			  
			  if(response[0] == 'y' || response[0] == 'Y')
					return 1;
			   else
				   return -1;
		   }
	}
	
	savedGames.push_back(filename);
	
	pathName = "./savedGames.json";
		 
    ofstream outputjsonFile(pathName, std::ios::out);
    JSONOutputArchive archive_out( outputjsonFile );
	
	archive_out( CEREAL_NVP(savedGames));	

   return 0;	
}

int gameLoadandSave::rmvGameFromList(string filename){
vector<string> savedGames;

	savedGames = getGameList();
	
	for(int i = 0; i < savedGames.size(); i++){
		if (savedGames[i] == filename){
			  savedGames.erase(savedGames.begin()+i);
			  pathName = "./savedGames.json";
			  	
			  ofstream outputjsonFile(pathName, std::ios::out);
			  JSONOutputArchive archive_out( outputjsonFile );
			  
			  archive_out( CEREAL_NVP(savedGames));
			  return 1;
		   }
	}	
	
	cout<<"file not found!"<<endl;
	
	return -1;
}