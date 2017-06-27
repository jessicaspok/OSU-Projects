#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <climits>
#include <bits/stdc++.h>
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/access.hpp"

#include "Game.h"
#include "Room.h"
#include "Object.h"
#include "Character.h"
#include "Detective.h"
#include "gameLoader.hpp"
#include "game_elements.hpp"

#define DEBUG 0
#define DEBUG_PRINT_LN if(DEBUG)

Game::Game()
{

}

void Game::configGame(gamePkg *g){
	
	g->thePlayer.setCurrentRoom(g->theRooms[BAR]);
	g->thePlayer.setPrevRoom(g->theRooms[FAKE]);

	//link rooms/connections
	g->theRooms[BAR]->addRoom(g->theRooms[HIDDEN], g->theRooms[TRENTFP], g->theRooms[MORGUE], g->theRooms[FAKE]);
	g->theRooms[HIDDEN]->addRoom(g->theRooms[FAKE], g->theRooms[BAR], g->theRooms[FAKE], g->theRooms[FAKE]);
	g->theRooms[POLICE]->addRoom(g->theRooms[PHARMACY], g->theRooms[BETHFP], g->theRooms[FAKE], g->theRooms[MOOSEFP]);
	g->theRooms[MORGUE]->addRoom(g->theRooms[FAKE], g->theRooms[PHARMACY], g->theRooms[FAKE], g->theRooms[BAR]);
	g->theRooms[PHARMACY]->addRoom(g->theRooms[MORGUE], g->theRooms[POLICE], g->theRooms[FAKE], g->theRooms[TRENTFP]);
	g->theRooms[BOBLR]->addRoom(g->theRooms[FAKE], g->theRooms[BOBOFF], g->theRooms[BOBFP], g->theRooms[BOBBR]);
	g->theRooms[BOBOFF]->addRoom(g->theRooms[BOBLR], g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[FAKE]);
	g->theRooms[BOBBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[BOBLR], g->theRooms[FAKE]);
	g->theRooms[BOBFP]->addRoom(g->theRooms[SAMFP], g->theRooms[FAKE], g->theRooms[CLAIREFP], g->theRooms[BOBLR]);
	g->theRooms[CLAIRELR]->addRoom(g->theRooms[FAKE], g->theRooms[CLAIREBUNK], g->theRooms[CLAIREBR], g->theRooms[CLAIREFP]);
	g->theRooms[CLAIREBUNK]->addRoom(g->theRooms[CLAIRELR], g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[FAKE]);
	g->theRooms[CLAIREBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[CLAIRELR]);
	g->theRooms[CLAIREFP]->addRoom(g->theRooms[BETHFP], g->theRooms[FAKE], g->theRooms[CLAIRELR], g->theRooms[BOBFP]);
	g->theRooms[BETHLR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[BETHBR], g->theRooms[BETHFP]);
	g->theRooms[BETHBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[BETHLR]);
	g->theRooms[BETHFP]->addRoom(g->theRooms[POLICE], g->theRooms[CLAIREFP], g->theRooms[BETHLR], g->theRooms[SAMFP]);
	g->theRooms[SAMLR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[SAMFP], g->theRooms[SAMBR]);
	g->theRooms[SAMBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[SAMLR], g->theRooms[FAKE]);
	g->theRooms[SAMFP]->addRoom(g->theRooms[MOOSEFP], g->theRooms[BOBFP], g->theRooms[BETHFP], g->theRooms[SAMLR]);
	g->theRooms[TRENTLR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[TRENTFP], g->theRooms[TRENTBR]);
	g->theRooms[TRENTBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[TRENTLR], g->theRooms[FAKE]);
	g->theRooms[TRENTFP]->addRoom(g->theRooms[BAR], g->theRooms[MOOSEFP], g->theRooms[PHARMACY], g->theRooms[TRENTLR]);
	g->theRooms[MOOSELR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[MOOSEFP], g->theRooms[MOOSEBR]);
	g->theRooms[MOOSEBR]->addRoom(g->theRooms[FAKE], g->theRooms[FAKE], g->theRooms[MOOSELR], g->theRooms[FAKE]);
	g->theRooms[MOOSEFP]->addRoom(g->theRooms[TRENTFP], g->theRooms[SAMFP], g->theRooms[POLICE], g->theRooms[MOOSELR]);	
	
	// add objects to rooms
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BARTRASH]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[VIAL]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BARCREATURE]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BARCHAIR]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BARTABLE]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BARBOOTH]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[BOOZE]);
	g->theRooms[BAR]->myObjects.push_back(g->theObjs[HIDDENDOOR]);
	
	g->theRooms[HIDDEN]->myObjects.push_back(g->theObjs[BARRAGS]);
	g->theRooms[HIDDEN]->myObjects.push_back(g->theObjs[TREVWALLET]);
	g->theRooms[HIDDEN]->myObjects.push_back(g->theObjs[BARSHELVES]);
	
	g->theRooms[MORGUE]->myObjects.push_back(g->theObjs[BOBBODY]);
	g->theRooms[MORGUE]->myObjects.push_back(g->theObjs[MORGUEDESK]);
	g->theRooms[MORGUE]->myObjects.push_back(g->theObjs[AUTOPSY]);
	
	g->theRooms[PHARMACY]->myObjects.push_back(g->theObjs[RECEIPT]);
	g->theRooms[PHARMACY]->myObjects.push_back(g->theObjs[PHARMCOOLERS]);
	g->theRooms[PHARMACY]->myObjects.push_back(g->theObjs[PHARMFREEZERS]);
	g->theRooms[PHARMACY]->myObjects.push_back(g->theObjs[PHARMSHELVES]);
	
	g->theRooms[POLICE]->myObjects.push_back(g->theObjs[POLBULLETIN]);
	g->theRooms[POLICE]->myObjects.push_back(g->theObjs[POLTABLE]);
	g->theRooms[POLICE]->myObjects.push_back(g->theObjs[BOBPHONE]);
	g->theRooms[POLICE]->myObjects.push_back(g->theObjs[WARRANT]);
	
	g->theRooms[BETHFP]->myObjects.push_back(g->theObjs[BETHDOOR]);
	g->theRooms[BETHFP]->myObjects.push_back(g->theObjs[BETHGARDEN]);
	
	g->theRooms[BETHLR]->myObjects.push_back(g->theObjs[BETHTABLE]);
	g->theRooms[BETHLR]->myObjects.push_back(g->theObjs[BETHBOX]);
	
	g->theRooms[BETHBR]->myObjects.push_back(g->theObjs[BETHBED]);
	g->theRooms[BETHBR]->myObjects.push_back(g->theObjs[BETHDRESSER]);
	
	g->theRooms[CLAIREFP]->myObjects.push_back(g->theObjs[CLAIREGNOME]);
	g->theRooms[CLAIREFP]->myObjects.push_back(g->theObjs[CLAIREFLAMINGOS]);
	g->theRooms[CLAIREFP]->myObjects.push_back(g->theObjs[CLAIREDOOR]);
	
	g->theRooms[CLAIRELR]->myObjects.push_back(g->theObjs[CLAIRETV]);
	g->theRooms[CLAIRELR]->myObjects.push_back(g->theObjs[CLAIRERUG]);
	g->theRooms[CLAIRELR]->myObjects.push_back(g->theObjs[BUNKDOOR]);
	
	g->theRooms[CLAIREBR]->myObjects.push_back(g->theObjs[CLAIREDRESSER]);
	g->theRooms[CLAIREBR]->myObjects.push_back(g->theObjs[CLAIREPICS]);
	g->theRooms[CLAIREBR]->myObjects.push_back(g->theObjs[CLAIREBED]);
	g->theRooms[CLAIREBR]->myObjects.push_back(g->theObjs[BUNKKEY]);
	
	g->theRooms[CLAIREBUNK]->myObjects.push_back(g->theObjs[CLAIRESHRINE]);
	g->theRooms[CLAIREBUNK]->myObjects.push_back(g->theObjs[PILLBOTTLE]);
	g->theRooms[CLAIREBUNK]->myObjects.push_back(g->theObjs[CLAIRECANS]);
	g->theRooms[CLAIREBUNK]->myObjects.push_back(g->theObjs[CLAIREWATER]);
	
	g->theRooms[BOBFP]->myObjects.push_back(g->theObjs[BOBCAR]);
	g->theRooms[BOBFP]->myObjects.push_back(g->theObjs[BOBCHESTS]);
	g->theRooms[BOBFP]->myObjects.push_back(g->theObjs[BOBRAGS]);
	g->theRooms[BOBFP]->myObjects.push_back(g->theObjs[BOBDOOR]);
	
	g->theRooms[BOBLR]->myObjects.push_back(g->theObjs[BOBTV]);
	g->theRooms[BOBLR]->myObjects.push_back(g->theObjs[BOBPOSTERS]);
	g->theRooms[BOBLR]->myObjects.push_back(g->theObjs[BOBGUITAR]);
	
	g->theRooms[BOBOFF]->myObjects.push_back(g->theObjs[BOBDESK]);
	g->theRooms[BOBOFF]->myObjects.push_back(g->theObjs[RING]);
	g->theRooms[BOBOFF]->myObjects.push_back(g->theObjs[BOBJERSEY]);
	g->theRooms[BOBOFF]->myObjects.push_back(g->theObjs[BOBCOMPUTER]);
	g->theRooms[BOBOFF]->myObjects.push_back(g->theObjs[BOBLOAN]);
	
	g->theRooms[BOBBR]->myObjects.push_back(g->theObjs[BOBBED]);
	g->theRooms[BOBBR]->myObjects.push_back(g->theObjs[BOBDRESSER]);
	g->theRooms[BOBBR]->myObjects.push_back(g->theObjs[BOBBOOKSHELF]);
	g->theRooms[BOBBR]->myObjects.push_back(g->theObjs[BOBNIGHTSTAND]);
	g->theRooms[BOBBR]->myObjects.push_back(g->theObjs[EMPTYBOTTLE]);
	
	g->theRooms[SAMFP]->myObjects.push_back(g->theObjs[SAMCHIMES]);
	g->theRooms[SAMFP]->myObjects.push_back(g->theObjs[SAMBIRDBATH]);
	g->theRooms[SAMFP]->myObjects.push_back(g->theObjs[SAMCAT]);
	g->theRooms[SAMFP]->myObjects.push_back(g->theObjs[SAMDOOR]);
	
	g->theRooms[SAMLR]->myObjects.push_back(g->theObjs[SAMCOUCH]);	
	g->theRooms[SAMLR]->myObjects.push_back(g->theObjs[SAMTABLE]);
	g->theRooms[SAMLR]->myObjects.push_back(g->theObjs[SAMPAPERLR]);
	g->theRooms[SAMLR]->myObjects.push_back(g->theObjs[SAMENTCENTER]);
	
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMBED]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMPAPERBR]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMDRESSER]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMFIGURINES]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMMEDICINE]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMSNACKS]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMDESK]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMLAPTOP]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMCODE]);
	g->theRooms[SAMBR]->myObjects.push_back(g->theObjs[SAMEMAILS]);
	
	g->theRooms[MOOSEFP]->myObjects.push_back(g->theObjs[MOOSETRUCK]);
	g->theRooms[MOOSEFP]->myObjects.push_back(g->theObjs[MOOSEMOTORCYCLE]);
	g->theRooms[MOOSEFP]->myObjects.push_back(g->theObjs[MOOSEDOOR]);
	
	g->theRooms[MOOSELR]->myObjects.push_back(g->theObjs[MOOSECOUCH]);
	g->theRooms[MOOSELR]->myObjects.push_back(g->theObjs[MOOSETABLELR]);
	g->theRooms[MOOSELR]->myObjects.push_back(g->theObjs[MOOSEPAPERS]);
	
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSEWATERBED]);
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSEBLANKETS]);
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSETABLEBR]);
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSEDRESSER]);
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSEBEERCANS]);
	g->theRooms[MOOSEBR]->myObjects.push_back(g->theObjs[MOOSECLOTHES]);
	
	g->theRooms[TRENTFP]->myObjects.push_back(g->theObjs[TRENTCHICKEN]);
	g->theRooms[TRENTFP]->myObjects.push_back(g->theObjs[TRENTDOOR]);
	
	g->theRooms[TRENTLR]->myObjects.push_back(g->theObjs[TRENTCOUCH]);
	g->theRooms[TRENTLR]->myObjects.push_back(g->theObjs[TRENTBIRDCAGE]);
	g->theRooms[TRENTLR]->myObjects.push_back(g->theObjs[TRENTBIRD]);
	g->theRooms[TRENTLR]->myObjects.push_back(g->theObjs[TRENTTABLE]);
	g->theRooms[TRENTLR]->myObjects.push_back(g->theObjs[TRENTPAPERS]);
	
	g->theRooms[TRENTBR]->myObjects.push_back(g->theObjs[TRENTBED]);
	g->theRooms[TRENTBR]->myObjects.push_back(g->theObjs[TRENTDRESSER]);
	g->theRooms[TRENTBR]->myObjects.push_back(g->theObjs[TRENTPOSTERS]);
	g->theRooms[TRENTBR]->myObjects.push_back(g->theObjs[TRENTDRUMS]);
	g->theRooms[TRENTBR]->myObjects.push_back(g->theObjs[TRENTGUITAR]);
	
	// add people to rooms
	g->theRooms[BETHLR]->myPeople.push_back(g->theChars[BETH]);
	g->theRooms[BETHLR]->myPeople.push_back(g->theChars[CLAIRE]);
	g->theRooms[MOOSELR]->myPeople.push_back(g->theChars[MOOSE]);
	g->theRooms[MOOSELR]->myPeople.push_back(g->theChars[SAM]);
	g->theRooms[MORGUE]->myPeople.push_back(g->theChars[FRANK]);
	g->theRooms[BAR]->myPeople.push_back(g->theChars[TRENT]);
	g->theRooms[TRENTBR]->myPeople.push_back(g->theChars[TREVOR]);
	g->theRooms[POLICE]->myPeople.push_back(g->theChars[ABE]);
	g->theRooms[PHARMACY]->myPeople.push_back(g->theChars[RORY]);
	
	// add objects to detective's inventory
	g->thePlayer.myObjects.push_back(g->theObjs[LIGHT]);
	g->thePlayer.myObjects.push_back(g->theObjs[LOCKPICK]);
	
	// initialize suspect list
	for (int i = 0; i < NUM_OF_CHARS; i++){
		if (g->theChars[i]->displayName != "Bobby")
			g->thePlayer.suspects.push_back(g->theChars[i]->displayName);
	}
}

gamePkg *Game::runGame(gamePkg *g)
{
	// parsing module functions
	string userInput = "";
	vector<string> parsedInput;
	Intent userIntent;
	
	userIntent.verb.push_back("");
	vector<string> verbs = {"go", "goto", "drive", "north", "south", "east", "west", "back", "look", "look at", "take", "pick", "pick up", "help", "hint", "inventory", "talk", 
						"arrest", "use", "enter", "knock", "break in", "drop", "savegame", "save", "edit", "drink", "consume",
						"load", "loadgame", "quit", "layout", "hack", "insight" };
	vector<string> prepositions = {"in", "on", "at", "up", "to"};  
	vector<string> nouns = { "bar", "morgue", "station", "policestation", "police", "pharmacy", "hidden", 
							"beth", "beth's","bobby", "bobby's","claire", "claire's","trent", "trent's", "trevor", "trevor's" ,"moose", "moose's",
							"sam", "sam's", "frank", "abe", "rory","house", "porch", "living", "livingroom", "bed", "beds", "bedroom", "couch", "bottle", "chair",
							"desk", "table", "report", "pill", "bottle", "ring", "light", "flashlight", "trash", "bin", "can", "stuffed", "creature", "booth", "rags",
							 "receipt", "wallet", "vial", "lockpick","cat", "booze", "beer", "note", "love", "coolers", "freezers", "shelves", "bulletin", "board",
							 "garden", "gnome", "flamingos", "dresser", "box", "tv", "photographs", "pictures", "photos", "posters", "guitar", "computer", "jersey", "bookshelf", 
							 "chimes", "birdbath", "nightstand", "chicken", "clothes", "cans", "can", "waterbed", "newspapers", "newspaper", "paper", "papers", "medicine", "model", "figurines", "snacks", "laptop",
							 "motorcycle", "blankets", "drum", "drums", "set", "drumset", "bunker", "booze", "phone", "birdcage", "bird", "truck", "entertainment", "chests", "car", "body",
							"shrine", "water", "emails", "code", "loan", "warrant", "autopsy", "bobPhone", "key", "door", "rug", "bike" // removed "room" 
							}; 
							
	cout << "You are currently in " << g->thePlayer.getCurrentRoom()->getDisplayName() << endl;

	// main while loop of the game
	while (!(userIntent.verb[0] == "quit" || userIntent.verb[0] == "savegame" || userIntent.verb[0] == "save")) { 
		// clear struct Intent Vector here after we check that one of the above strings isn't in it
		clearVector(userIntent.verb);
		clearVector(userIntent.noun);		
		clearVector(userIntent.preposition);
		clearVector(userIntent.verbEnumType);
		
		sandsOfTime(g);
		
		DEBUG_PRINT_LN	cout << "Before getUserInput" << endl;
		
		cout << endl << "What would you like to do? ";
		userInput = getUserInput();
		
		DEBUG_PRINT_LN cout << "Before tokenizeInput" << endl;
		
		parsedInput = tokenizeInput(userInput, 50);
		
		DEBUG_PRINT_LN cout << "Before extractIntent" << endl;
		
		userIntent = extractIntent(parsedInput, verbs, nouns, prepositions);
		
        DEBUG_PRINT_LN cout << "Before verbEnumerator Loop" << endl;
		
		for (int i = 0; i < userIntent.verb.size(); i++) {
			int en = verbEnumerator(userIntent.verb[i]);
			userIntent.verbEnumType.push_back(en);
		}
		if(userIntent.verb.size() == 0){
			// code for dealing with soley noun based directional movement
			userIntent.verbEnumType.push_back(ELSEIT);
			userIntent.verb.push_back("none");
		}
		DEBUG_PRINT_LN cout << "Before nounAliasMassager Loop" << endl;		
		for (int i = 0; i < userIntent.noun.size(); i++) {
			string en = nounAliasMassager(userIntent.noun[i]);
			userIntent.noun.at(i) = en;
		}
		
		if(userIntent.verb[0] == "loadgame" || userIntent.verb[0] == "load"){
			gamePkg *temp = loadGame("");
			if(temp == NULL)				
				continue;
			else{
				delete g;
				g = temp;
				continue;
			}
		}
		
		twoToOneString(userIntent);
		
		action(userIntent, g);
	}	

getname:	
	if (userIntent.verb[0] == "quit" || userIntent.verb[0] == "savegame" || userIntent.verb[0] == "save") {
		if(userIntent.verb[0] == "quit"){
			cout<<"\nWould you like to save this game before quitting? [Y/N] ";
			getline (cin, userInput);
			if(userInput[0] == 'n' || userInput[0] == 'N')
				return g;
		    }
		    
	    cout<<"WHAT WOULD YOU LIKE TO SAVE THIS GAME AS? ";
		getline (cin, userInput);

		transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
		if(userInput == "game"){
			cout<<"\nThat's the one name I reject! Try naming it something else..."<<endl;
			goto getname;
		}
		
		saveGame(g, userInput);
	}
	
return g;	
}

gamePkg *Game::initGame() 
{
	
	//DEBUG_PRINT_LN generate();	//generate a new game for debug purposes.
  
    return loadGame("new");    //read in new game from default files
}

		
gamePkg *Game::generate(){

	vector<shared_ptr<Room>> listRoom;
		vector<shared_ptr<Object>> roomObjs[NUM_OF_ROOMS];
		vector<shared_ptr<Character>> people[NUM_OF_ROOMS];
		
	vector<shared_ptr<Character>> listCharacter;
	vector<shared_ptr<Object>> listObject;
		
	//create baseline rooms, maintain this list order
	//shared_ptr<Room> bar(new Room (roomName[BAR], "sd", "ld", "hint", roomObjs[BAR], reqObjs[BAR], people[BAR], 0));
	//listRoom.push_back(bar);
	CREATE_ROOM(fake,		FAKE       );
	CREATE_ROOM(bar,		BAR        );
	CREATE_ROOM(hidden,		HIDDEN     );
	CREATE_ROOM(police,		POLICE     );
	CREATE_ROOM(morgue,		MORGUE     );
	CREATE_ROOM(pharmacy,	PHARMACY   );
	CREATE_ROOM(bobLR,		BOBLR      );
	CREATE_ROOM(bobOFF,		BOBOFF     );
	CREATE_ROOM(bobBR,		BOBBR      );
	CREATE_ROOM(bobFP,		BOBFP      );
	CREATE_ROOM(claireLR,	CLAIRELR   );
	CREATE_ROOM(claireBUNK,	CLAIREBUNK );
	CREATE_ROOM(claireBR,	CLAIREBR   );
	CREATE_ROOM(claireFP,	CLAIREFP   );
	CREATE_ROOM(bethLR,		BETHLR     );
	CREATE_ROOM(bethBR,		BETHBR     );
	CREATE_ROOM(bethFP,		BETHFP     );
	CREATE_ROOM(samLR,		SAMLR      );
	CREATE_ROOM(samBR,		SAMBR      );
	CREATE_ROOM(samFP,		SAMFP      );
	CREATE_ROOM(trentLR,	TRENTLR    );
	CREATE_ROOM(trentBR,	TRENTBR    );
	CREATE_ROOM(trentFP,	TRENTFP    );
	CREATE_ROOM(mooseLR,	MOOSELR    );
	CREATE_ROOM(mooseBR,	MOOSEBR    );
	CREATE_ROOM(mooseFP,	MOOSEFP    );
	
	// default dialogue for each character
	vector<string> dialogue {"1st time speaking", "2nd time speaking"};
	
	//create all characters
	//shared_ptr<Character> beth  (new Character (characterName[BETH], charDisplayName[BETH], charLongDesc[BETH], 0, "hint", dialogue));  listCharacter.push_back(beth);
	CREATE_CHAR(beth,		BETH   );
	CREATE_CHAR(claire,		CLAIRE );
	CREATE_CHAR(sam,		SAM    );
	CREATE_CHAR(frank,		FRANK  );
	CREATE_CHAR(trent,		TRENT  );
	CREATE_CHAR(trevor,		TREVOR );
	CREATE_CHAR(moose,		MOOSE  );
	CREATE_CHAR(abe,		ABE    );
	CREATE_CHAR(rory,		RORY   );
	
	Detective me;
	
	
	//shared_ptr<Object> trevWallet (new Object (objName[TREVWALLET], "ld", "sd", vVerbs, true));		listObject.push_back(trevWallet);
	CREATE_OBJ(trevWallet,		TREVWALLET 		);
	CREATE_OBJ(vial,	    	VIAL       		);
	CREATE_OBJ(loveNote,		LOVENOTE   		);
	CREATE_OBJ(autopsy,	    	AUTOPSY    		);
	CREATE_OBJ(receipt,	    	RECEIPT    		);
	CREATE_OBJ(pillBottle,		PILLBOTTLE 		);
	CREATE_OBJ(ring,	    	RING       		);
	CREATE_OBJ(bobPhone,		BOBPHONE  		);
	CREATE_OBJ(lockPick,		LOCKPICK   		);
	CREATE_OBJ(light,	    	LIGHT      		);
	CREATE_OBJ(suspectList,		SUSPECTLIST		);
	CREATE_OBJ(barTrash,		BARTRASH		);
	CREATE_OBJ(barCreature,		BARCREATURE		);
	CREATE_OBJ(barChair,		BARCHAIR		);
	CREATE_OBJ(barTable,		BARTABLE		);
	CREATE_OBJ(barBooth,		BARBOOTH		);
	CREATE_OBJ(barRags,			BARRAGS			);
	CREATE_OBJ(barShelves,		BARSHELVES		);
	CREATE_OBJ(bobBody,			BOBBODY			);
	CREATE_OBJ(morgueDesk,		MORGUEDESK		);
	CREATE_OBJ(pharmCoolers,	PHARMCOOLERS	);
	CREATE_OBJ(pharmFreezers,	PHARMFREEZERS	);
	CREATE_OBJ(pharmShelves,	PHARMSHELVES	);
	CREATE_OBJ(polBulletin,		POLBULLETIN		);
	CREATE_OBJ(polTable,		POLTABLE		);
	CREATE_OBJ(bethDoor,		BETHDOOR		);
	CREATE_OBJ(bethGarden,		BETHGARDEN		);
	CREATE_OBJ(bethTable,		BETHTABLE		);
	CREATE_OBJ(bethBox,			BETHBOX			);
	CREATE_OBJ(bethBed,			BETHBED			);
	CREATE_OBJ(bethDresser,		BETHDRESSER		);
	CREATE_OBJ(claireGnome,		CLAIREGNOME		);
	CREATE_OBJ(claireFlamingos,	CLAIREFLAMINGOS	);
	CREATE_OBJ(claireDoor,		CLAIREDOOR	 	);
	CREATE_OBJ(claireTV,		CLAIRETV	 	);
	CREATE_OBJ(claireRug,		CLAIRERUG	 	);
	CREATE_OBJ(claireDresser,	CLAIREDRESSER	);
	CREATE_OBJ(clairePics,		CLAIREPICS		);
	CREATE_OBJ(claireShrine,	CLAIRESHRINE	);
	CREATE_OBJ(claireCans,		CLAIRECANS		);
	CREATE_OBJ(claireWater,		CLAIREWATER		);
	CREATE_OBJ(bobCar,			BOBCAR			);
	CREATE_OBJ(bobChests,		BOBCHESTS		);
	CREATE_OBJ(bobRags,			BOBRAGS			);
	CREATE_OBJ(bobDoor,			BOBDOOR			);
	CREATE_OBJ(bobTV,			BOBTV			);
	CREATE_OBJ(bobPosters,		BOBPOSTERS		);
	CREATE_OBJ(bobGuitar,		BOBGUITAR		);
	CREATE_OBJ(bobDesk,			BOBDESK			);
	CREATE_OBJ(bobJersey,		BOBJERSEY		);
	CREATE_OBJ(bobComputer,		BOBCOMPUTER		);
	CREATE_OBJ(bobBed,			BOBBED			);
	CREATE_OBJ(bobDresser,		BOBDRESSER		);
	CREATE_OBJ(bobBookshelf,	BOBBOOKSHELF	);
	CREATE_OBJ(bobNightstand,	BOBNIGHTSTAND	);
	CREATE_OBJ(samChimes,		SAMCHIMES		);
	CREATE_OBJ(samBirdbath,		SAMBIRDBATH		);
	CREATE_OBJ(samCat,			SAMCAT			);
	CREATE_OBJ(samDoor,			SAMDOOR			);
	CREATE_OBJ(samCouch,		SAMCOUCH		);
	CREATE_OBJ(samTable,		SAMTABLE		);
	CREATE_OBJ(samPaperLR,		SAMPAPERLR		);
	CREATE_OBJ(samEntCenter,	SAMENTCENTER	);
	CREATE_OBJ(samBed,			SAMBED			);
	CREATE_OBJ(samPaperBR,		SAMPAPERBR		);
	CREATE_OBJ(samDresser,		SAMDRESSER		);
	CREATE_OBJ(samFigurines,	SAMFIGURINES	);
	CREATE_OBJ(samMedicine,		SAMMEDICINE		);
	CREATE_OBJ(samSnacks,		SAMSNACKS		);
	CREATE_OBJ(samDesk,			SAMDESK			);
	CREATE_OBJ(samLaptop,		SAMLAPTOP		);
	CREATE_OBJ(mooseTruck,		MOOSETRUCK		);
	CREATE_OBJ(mooseMotorcycle,	MOOSEMOTORCYCLE	);
	CREATE_OBJ(mooseDoor,		MOOSEDOOR		);
	CREATE_OBJ(mooseCouch,		MOOSECOUCH		);
	CREATE_OBJ(mooseTableLR,	MOOSETABLELR	);
	CREATE_OBJ(moosePapers,		MOOSEPAPERS		);
	CREATE_OBJ(mooseWaterbed,	MOOSEWATERBED	);
	CREATE_OBJ(mooseBlankets,	MOOSEBLANKETS	);
	CREATE_OBJ(mooseTableBR,	MOOSETABLEBR	);
	CREATE_OBJ(mooseDresser,	MOOSEDRESSER	);
	CREATE_OBJ(mooseBeerCans,	MOOSEBEERCANS	);
	CREATE_OBJ(mooseClothes,	MOOSECLOTHES	);
	CREATE_OBJ(trentChicken,	TRENTCHICKEN	);
	CREATE_OBJ(trentDoor,		TRENTDOOR		);
	CREATE_OBJ(trentCouch,		TRENTCOUCH		);
	CREATE_OBJ(trentBirdcage,	TRENTBIRDCAGE	);
	CREATE_OBJ(trentBird,		TRENTBIRD		);
	CREATE_OBJ(trentTable,		TRENTTABLE		);
	CREATE_OBJ(trentPapers,		TRENTPAPERS		);
	CREATE_OBJ(trentBed,		TRENTBED		);
	CREATE_OBJ(trentDresser,	TRENTDRESSER	);
	CREATE_OBJ(trentPosters,	TRENTPOSTERS	);
	CREATE_OBJ(trentDrums,		TRENTDRUMS		);
	CREATE_OBJ(trentGuitar,		TRENTGUITAR		);
	CREATE_OBJ(bunkDoor,		BUNKDOOR		);
	CREATE_OBJ(booze,			BOOZE			);
	CREATE_OBJ(code,			SAMCODE			);
	CREATE_OBJ(emails,			SAMEMAILS		);
	CREATE_OBJ(loan,			BOBLOAN			);
	CREATE_OBJ(warrant,			WARRANT			);
	CREATE_OBJ(claireBed,		CLAIREBED		);
	CREATE_OBJ(hiddenDoor,		HIDDENDOOR		);
	CREATE_OBJ(emptyBottle,		EMPTYBOTTLE		);
	CREATE_OBJ(bunkKey,			BUNKKEY			);
	
	gamePkg *mybundle = new gamePkg();
		mybundle->theChars 	= 	listCharacter;
		mybundle->theObjs	= 	listObject;
		mybundle->theRooms	=	listRoom;
		mybundle->thePlayer	=	me;
	

	//!!!!!!!!!!!!!!!!!!!!CONFIGURE GAME HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!
	configGame(mybundle);
	
	gameLoadandSave *gameFiles = new gameLoadandSave();	
	gameFiles->generateGame(mybundle);

	return mybundle;
}

gamePkg *Game::loadGame(string filename) 
{
	
	vector<Room> listRoom;
	vector<Character> listCharacter;
	vector<Object> listObject;	

    vector<string> savedGames;	
	int response;

    gameLoadandSave *gameFiles = new gameLoadandSave();
     
	// if its a new game, just read in default game files
	if(filename == "new")
		return gameFiles->loadNewGame(roomName,characterName,objName, "player");
		
	savedGames = gameFiles->getGameList();
	
	cout << "Your saved games are: " << endl;
	for(int i = 1; i < savedGames.size(); i++){
		cout << "[" << i << "]\t" << savedGames[i]<<endl;
	}

loop:	
	cout << "Enter index number to load, or 0 to cancel...:" << endl;
	cin >> response;
	cin.clear();
    cin.ignore(INT_MAX, '\n'); 	
	
	if(response == 0)
	     return NULL;
	else 
	   if(response >= 1 && response < savedGames.size()){
		 DEBUG_PRINT_LN cout << "load this file "<<savedGames[response] << endl;
		 return gameFiles->loadGame(roomName,characterName,objName, "player", savedGames[response]); 
		}
	else
	    goto loop;
	  
}

int Game::saveGame(gamePkg *newBundle,string filename) 
{
	//TODO: will be implemented with Tunde's functions
	 gameLoadandSave *gameFiles = new gameLoadandSave();
	 if(gameFiles->addGameToList(filename)!= -1) 
			gameFiles->saveGame(newBundle, filename);
}


void Game::deleteGame(){
    vector<string> savedGames;	
	int response;

    gameLoadandSave *gameFiles = new gameLoadandSave();

	savedGames = gameFiles->getGameList();

	cout<<"Your saved games are: "<<endl;
	for(int i = 1; i < savedGames.size(); i++){
		cout<<"["<<i<<"]\t"<<savedGames[i]<<endl;
	}

loop:	
	cout<<"Enter index number to delete, or 0 exit...:"<<endl;
	cin>>response;
	cin.clear();
    cin.ignore(INT_MAX, '\n'); 	
	
	if(response == 0)
		return;
	else 
	   if(response >= 1 && response < savedGames.size()){
		 DEBUG_PRINT_LN cout<<"delete this game file --> "<<savedGames[response]<<endl;
		 gameFiles->deleteGame(savedGames[response]); 
		 return;
		}
	else
	    goto loop;	
	
}


void Game::sandsOfTime(gamePkg *mybundle){
	
	if((find((mybundle->theRooms[MOOSELR])->myPeople, "moose"))->hasTalkedTo < 2){ 
		if(mybundle->thePlayer.isInInventory("bobPhone")){
			if((mybundle->thePlayer.getFromInventory("bobPhone"))->getIsLocked() == false){
				shared_ptr<Character> tempChar = find((mybundle->theRooms[MOOSELR])->myPeople, "moose"); 
				DEBUG_PRINT_LN cout << tempChar->getName() << endl;
				tempChar->setHasTalkedTo(2);
				DEBUG_PRINT_LN cout << "Via bundle: " << (mybundle->theRooms[MOOSELR])->myPeople[0] << " " << (mybundle->theChars[MOOSE])->hasTalkedTo << endl;
				cout << "You search through Bobby's text messages and find some threatening messages from Moose." << endl;
				tempChar = find((mybundle->theRooms[BETHLR])->myPeople, "beth");
				tempChar->setHasTalkedTo(2);
				tempChar = find((mybundle->theRooms[MOOSELR])->myPeople, "sam");
				tempChar->setHasTalkedTo(2);
				tempChar = find((mybundle->theRooms[POLICE])->myPeople, "abe");
				tempChar->setHasTalkedTo(2);				
			}
		
		}
	}
	
	if((find((mybundle->theRooms[POLICE])->myPeople, "abe"))->hasTalkedTo == 2 && mybundle->thePlayer.isInInventory("warrant")){
		shared_ptr<Character> tempChar = find((mybundle->theRooms[POLICE])->myPeople, "abe");
		tempChar->setHasTalkedTo(3);
	}	

	if((find((mybundle->theRooms[MOOSELR])->myPeople, "sam"))->hasTalkedTo == 2){
			if(mybundle->thePlayer.isInInventory("emails")){
				shared_ptr<Character> tempChar = find((mybundle->theRooms[MOOSELR])->myPeople, "sam");
				tempChar->setHasTalkedTo(3);
				tempChar = find((mybundle->theRooms[POLICE])->myPeople, "abe");
				tempChar->setHasTalkedTo(4);				
			}
	}	

	if((find((mybundle->theRooms[PHARMACY])->myPeople, "rory"))->hasTalkedTo < 2){
		if(mybundle->thePlayer.isInInventory("autopsy")){
				shared_ptr<Character> tempChar = find((mybundle->theRooms[PHARMACY])->myPeople, "rory");
				tempChar->setHasTalkedTo(2);	
				shared_ptr<Object> tempObj = find(mybundle->theRooms[PHARMACY]->myObjects, "receipt");
				tempObj->setHidden(false);
		}	
	}
	
	if((find((mybundle->theRooms[BETHLR])->myPeople, "beth"))->hasTalkedTo == 2){
			if(mybundle->thePlayer.isInInventory("receipt")){
				shared_ptr<Character> tempChar = find((mybundle->theRooms[BETHLR])->myPeople, "beth");
				tempChar->setHasTalkedTo(3);
				tempChar = find((mybundle->theRooms[BETHLR])->myPeople, "claire");
				tempChar->setHasTalkedTo(2);
			}
	}
	if(find((mybundle->theRooms[BAR])->myPeople, "trent") != nullptr){
		if((find((mybundle->theRooms[BAR])->myPeople, "trent"))->hasTalkedTo < 2){
				if(mybundle->thePlayer.isInInventory("loan")){
					shared_ptr<Character> tempChar = find((mybundle->theRooms[BAR])->myPeople, "trent");
					tempChar->setHasTalkedTo(2);
				}
		}	
	}
	
	if(find((mybundle->theRooms[BAR])->myPeople, "trent") != nullptr){
		if((find((mybundle->theRooms[BAR])->myPeople, "trent"))->hasTalkedTo == 2 && (mybundle->thePlayer.getCurrentRoom())->getName() == "bar"){ 
			if(mybundle->thePlayer.isInInventory("loan")){
				shared_ptr<Character> tempChar = find((mybundle->theRooms[BAR])->myPeople, "trent");
				tempChar->setHasTalkedTo(3);
				DEBUG_PRINT_LN cout << "BEfore Add" << endl;
				DEBUG_PRINT_LN cout << "AFter Add" << endl;				
				cout << "You here a crashing sound come from somewhere in the back, but you can't exactly make out where. You eye-ball Trent really hard, expecting an explanation." << endl;
				for(int i = 0; i < mybundle->theRooms[BAR]->myObjects.size(); i++){
					if (mybundle->theRooms[BAR]->myObjects[i]->isLocked == true){
						mybundle->theRooms[BAR]->myObjects[i]->setIsLocked(false);
						cout << "(Trent walks over to the broom closet, opens it, then flicks a secret switch and a small panel opens out)" << endl;
						(mybundle->theRooms[BAR])->setShortDescription("You enter back into the Thirsty Whistle.\nTo the North you see the now exposed hidden panel to the secret room open. To the East is the Morgue.\n");
						(mybundle->theRooms[BAR])->setLongDescription("You step into the Thirsty Whistle, the aura of death still lingering about. The establishment has all the expected \n"
															"trappings of a small town bar, with dated decor, a lack of windows, and a faux taxidermized creature one could at least\n"
															"gather was part eagle and part snake. The place was barren, death has that affect. Along the walls are booths, with \n"
															"some round tables and accompanying chairs around the center. To your left, a stage that is clearly the focal point of \n"
															"karaoke Wednesdays. To the right is the actual bar, however, you don't see the bartender. In the back you see a \n"
															"corner booth sectioned off with police tape, and nearby a small hall with a door to a broom closet that is open, the hidden room exposed.\n"
															"To the East is the Morgue.\n");
					}
				}
			}	
		}
	}	

	if(find((mybundle->theRooms[BAR])->myPeople, "trent") != nullptr){	
		if(mybundle->thePlayer.isInInventory("trevWallet") && (find((mybundle->theRooms[BAR])->myPeople, "trent"))->hasTalkedTo == 3){ 
				shared_ptr<Character> tempChar = find((mybundle->theRooms[BAR])->myPeople, "trent");
				tempChar->setHasTalkedTo(4);

		}
	}
	
	if(mybundle->thePlayer.isInInventory("trevWallet") && (find((mybundle->theRooms[TRENTBR])->myPeople, "trevor"))->hasTalkedTo <= 1){ 
			shared_ptr<Character> tempChar = find((mybundle->theRooms[TRENTBR])->myPeople, "trevor");
			tempChar->setHasTalkedTo(2);
			tempChar = find((mybundle->theRooms[BETHLR])->myPeople, "claire");
			tempChar->setHasTalkedTo(3);
	}
	if(find((mybundle->theRooms[BETHLR])->myPeople, "claire") != nullptr){
		if((find((mybundle->theRooms[BETHLR])->myPeople, "claire"))->hasTalkedTo == 3 && (mybundle->thePlayer.getCurrentRoom())->getName() == "bethLR"){
			cout << "You step in to confront Claire about what Trevor said, her eyes widening as you finish. She replies:" << endl;
			shared_ptr<Character> tempChar = find((mybundle->theRooms[BETHLR])->myPeople, "claire");
			tempChar->speak();
			tempChar->setHasTalkedTo(4);
			(mybundle->theRooms[BETHLR])->myPeople.pop_back();
			(mybundle->theRooms[BAR])->myPeople.pop_back();
			(mybundle->theRooms[BAR])->setShortDescription("You enter back into the Thirsty Whistle.\n  To the East is the Morgue.\n");
			(mybundle->theRooms[BAR])->setLongDescription("You step into the Thirsty Whistle, the aura of death still lingering about. The establishment has all the expected \n"
															"trappings of a small town bar, with dated decor, a lack of windows, and a faux taxidermized creature one could at least\n"
															"gather was part eagle and part snake. The place was barren, death has that affect. Along the walls are booths, with \n"
															"some round tables and accompanying chairs around the center. To your left, a stage that is clearly the focal point of \n"
															"karaoke Wednesdays. To the right is the actual bar, however, you don't see the bartender. In the back you see a \n"
															"corner booth sectioned off with police tape, and nearby a small hall with a door to a broom closet that is open, the hidden room exposed.\n"
															"To the East is the Morgue.\n");
			(mybundle->theRooms[CLAIRELR])->setShortDescription("You are in Claire's living room, although you notice right away that the place looks a bit in a shiveled mess,\n"
																"with the large rug in the middle of the floor partially flipped up on itself, revealing what looks like the corner of a metal door.\n"
																"The door to the porch is to the West and Claire's bedroom to the East.\n");
			(mybundle->theRooms[CLAIRELR])->setLongDescription("You are standing in Claire's living room. The furniture is old, perhaps a mixture of the 70's and 80's with a few \n"
																"contemporary replacements such as the television and other electronics. To the east is a door to Claire's bedroom, \n"
																"and behind you to the west is the front door that leads out to Claire's porch. The outdoor theme of painted sunflowers \n"
																"has seeped into the place, continuing across the walls and reflecting in various indoor type Knick knacks as well as \n"
																"the large sunflower shaped throw run on the hardwood floor that has been flipped up on itself, revealing the corner of a metal door.\n");												
		}
	}	
}