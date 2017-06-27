#include "parsing_module.hpp"

#define DEBUG 0
#define DEBUG_PRINT_LN if(DEBUG)
	
// Function Gets User Input in the form of a STL string from the command line
std::string getUserInput() {		
	std::string userInput;
	getline(std::cin, userInput);
	return userInput;
}

// Function tokenizes string of words into a vector of strings
std::vector<std::string> tokenizeInput(std::string userInputString, int maxWordSize) {
	std::vector<std::string> parsedInput;
	parsedInput.reserve(10);
	char* buffer = new char[maxWordSize];
	std::stringstream ss;
	ss << userInputString;
	while (ss.getline(buffer, maxWordSize, ' ')) {
		parsedInput.push_back(buffer);
	}
	delete buffer;
	return parsedInput;
}

// Function compares a vector of strings with passed in vectors of valid verbs and nouns, returning a struct that contains a verb and noun
struct Intent extractIntent(std::vector<std::string> parsedInput, std::vector<std::string> verbsVec, std::vector<std::string> nounsVec, std::vector<std::string> prepositionsVec) {
	struct Intent getIntent;
	std::string oppCap;

	for (int i = 0; i < parsedInput.size(); i++) {
	DEBUG_PRINT_LN cout << "Input String: " << parsedInput[i] << endl;
		bool wasVerb = false, wasPrep = false , wasNoun = false;
		int verbIndex, prepIndex, nounIndex = 0;
		for (int j = 0; j < verbsVec.size(); j++) {
			if (parsedInput[i] == verbsVec[j]) {
				getIntent.verb.push_back(verbsVec[j]);
				wasVerb = true;
				verbIndex++;
	DEBUG_PRINT_LN cout << "Verb is: " << verbsVec[j] << endl;
				continue;
			}
			oppCap.assign(parsedInput[i]);
			oppCap = reverseCapitalization(oppCap);
			if (oppCap == verbsVec[j]) {
				getIntent.verb.push_back(verbsVec[j]);
				wasVerb = true;
				verbIndex++;
				continue;
			}
		}

		if(wasVerb == false){ 
			if(verbIndex == i){getIntent.verb.push_back("none");}

			for (int l = 0; l < prepositionsVec.size(); l++) {
				if (parsedInput[i] == prepositionsVec[l]) {
					getIntent.preposition.push_back(prepositionsVec[l]);
					wasPrep = true;
					prepIndex++;
	DEBUG_PRINT_LN cout << "Prep is: " << prepositionsVec[l] << endl;
					continue;
				}
				oppCap.assign(parsedInput[i]);
				oppCap = reverseCapitalization(oppCap);
				if (oppCap == prepositionsVec[l]) {
					getIntent.preposition.push_back(prepositionsVec[l]);
					wasPrep = true;
					prepIndex++;
					continue;
				}
			}

			if (wasPrep == false) {
				if(prepIndex == i){ getIntent.preposition.push_back("none"); }

				for (int k = 0; k < nounsVec.size(); k++) {
					if (parsedInput[i] == nounsVec[k]) {
						getIntent.noun.push_back(nounsVec[k]);
						nounIndex++;
						wasNoun = true;
	DEBUG_PRINT_LN cout << "Noun is: " << nounsVec[k] << endl;
					}
					oppCap.assign(parsedInput[i]);
					oppCap = reverseCapitalization(oppCap);
					if (oppCap == nounsVec[k]) {
						getIntent.noun.push_back(nounsVec[k]);
						nounIndex++;
						wasNoun = true;
					}
				}
			}
		}
	}
	if(getIntent.preposition.size() == 0){getIntent.preposition.push_back("none");}
	if(getIntent.noun.size() == 0){getIntent.noun.push_back("none");}
	return getIntent;
}

// Function changes cases of first letter of word
std::string reverseCapitalization(std::string string) {
		if (string[0] < 'a') {
		string[0] = string[0] + 32;
	}
	else {
		string[0] = string[0] - 32;
	}
	return string;
}

// Takes verb string and returns enumerated value for synonyms
int verbEnumerator(std::string verb) {
	if (verb == "go" || verb == "goto" || verb == "north" || verb == "south" || verb == "east" || verb == "west" || verb == "walk" || verb == "run" || verb == "move" || verb == "back" || verb == "drive") { // Move Type Command
		return 1;}
	if (verb == "look") {
		return 2;}
	if (verb == "take" || verb == "grab" || verb == "get" || verb == "pick") {
		return 3;}
	if (verb == "help" || verb == "commands") {
		return 4;}
	if (verb == "hint") {
		return 5;}
	if (verb == "inventory" || verb == "bag" || verb == "pack") {
		return 6;}
	if (verb == "talk" || verb == "ask" || verb == "converse" || verb == "chat") {
		return 7;}
	if (verb == "arrest") {
		return 8;}
	if (verb == "use" || verb == "interact") {
		return 9;}
	if (verb == "enter") {
		return 10;}
	if (verb == "knock" || verb == "ring") {
		return 11;}
	if (verb == "drop" || verb == "place") {
		return 12;}
	if (verb == "hack") {
		return 13;}
	if (verb == "drink" || verb == "consume") {
		return 14;}
	if (verb == "break" || verb == "force") {
		return 15;}
	if(verb == "insight"){
		return 16;}
	if(verb == "edit"){
		return 17;}
	if(verb == "layout"){
		return 18;}
	else{return 0;}
}

// Takes noun string and returns enumerated value for synonyms
std::string nounAliasMassager(std::string noun) {
	if (noun == "claire" || noun == "claire's" || noun == "claires'") 
	{return "claire";}
	if (noun == "beth" || noun == "beth's") 
	{return "beth";}
	if (noun == "bobby" || noun == "bobby's" || noun == "bobbies'") 
	{return "bob";}
	if (noun == "sam" || noun == "sam's" || noun == "sams'") 
	{return "sam";}
	if (noun == "trevor" || noun == "trevor's" || noun == "trev")
	{return "trevor";}
	if (noun == "moose" || noun == "moose's")
	{return "moose";}
	if (noun == "trent" || noun == "trent's")
	{return "trent";}
	if (noun == "bar") 
	{return "bar";}
	if (noun == "police" || noun == "station" || noun == "precinct" || noun == "pd" || noun == "PD" || noun == "policestation") 
	{return "police";}
	//if (noun == "morgue") 
	//{return "morgue";}
	if (noun == "pharmacy" || noun == "store") 
	{return "pharmacy";}
	if (noun == "hidden")
	{return "hidden";}
	if (noun == "porch" || noun == "front" || noun == "house") 
	{return "porch";}
	if (noun == "receipt")
	{return "receipt";}
	if (noun == "couch" || noun == "sofa") 
	{return "couch";}
	if (noun == "wallet")
	{return "trevWallet";}
	if (noun == "lockpick" || noun == "pick")
	{return "lockpick";}
	if(noun == "bobPhone")
	{return "bobPhone";}
	if(noun == "trash" || noun == "bin")
	{return "trash";}
	if(noun == "booze" || noun == "Booze" || noun == "beer" || noun == "can" || noun == "cans")
	{return "beer";}
	if(noun == "love" || noun == "note" || noun == "lovenote")
	{return "loveNote";}
	if(noun == "pill" || noun == "bottle")
	{return "pillBottle";}
	if(noun == "light" || noun == "flashlight")
	{return "light";}
	if(noun == "pics" || noun == "photographs" || noun == "photos")
	{return "pictures";}
	if(noun == "beds"){
		return "bed";}
	if(noun == "living" || noun == "livingroom")
	{return "livingroom";}
	if(noun == "stuffed" || noun == "creature")
	{return "creature";}
	if(noun == "report")
	{return "autopsy";}
	if(noun == "drum" || noun == "drumset" || noun == "set")
	{return "drums";}
	if(noun == "paper" || noun == "papers" || noun == "newspaper")
	{return "newspapers";}
	if(noun == "phone")
	{return "bobPhone";}
	if(noun == "bike")
	{return "motorcycle";}
return noun;		
//return "none";
}

void twoToOneString(struct Intent &intention){
	for(int i = 0; i < intention.noun.size() - 1; i++){
		//BOB
		if(intention.noun[i] == "bob" && intention.noun[i+1] == "bobPhone"){intention.noun[i] = "bobPhone"; return;}
		if(intention.noun[i] == "bob" && (intention.noun[i+1] == "livingroom" || intention.noun[i+1] == "living")){intention.noun[i] = "bobLR"; return;}
		if(intention.noun[i] == "bob" && intention.noun[i+1] == "office"){intention.noun[i] = "bobOFF";	return;	}
		if(intention.noun[i] == "bob" && intention.noun[i+1] == "bedroom"){	intention.noun[i] = "bobBR";return;	}
		if(intention.noun[i] == "bob" && intention.noun[i+1] == "porch"){intention.noun[i] = "bobFP";return;}
		if(intention.noun[i] == "bob" && intention.noun[i+1] == "body"){intention.noun[i] = "body"; return;}
		//CLAIRE 
		if(intention.noun[i] == "claire" && intention.noun[i+1] == "bunker"){intention.noun[i] = "claireBUNK";return;}
		if(intention.noun[i] == "claire" && intention.noun[i+1] == "livingroom"){intention.noun[i] = "claireLR";return;}
		if(intention.noun[i] == "claire" && intention.noun[i+1] == "bedroom"){intention.noun[i] = "claireBR";return;}
		if(intention.noun[i] == "claire" && intention.noun[i+1] == "porch"){intention.noun[i] = "claireFP";return;}
		//SAM 
		if(intention.noun[i] == "sam" && intention.noun[i+1] == "livingroom"){intention.noun[i] = "samLR";return;}
		if(intention.noun[i] == "sam" && intention.noun[i+1] == "bedroom"){intention.noun[i] = "samBR";return;}
		if(intention.noun[i] == "sam" && intention.noun[i+1] == "porch"){intention.noun[i] = "samFP";return;}
		//TRENT 
		if(intention.noun[i] == "trent" && (intention.noun[i+1] == "livingroom" || intention.noun[i+1] == "living")){intention.noun[i] = "trentLR";return;}
		if(intention.noun[i] == "trent" && intention.noun[i+1] == "bedroom"){intention.noun[i] = "trentBR";return;}
		if(intention.noun[i] == "trent" && intention.noun[i+1] == "porch"){intention.noun[i] = "trentFP";return;}
		//MOOSE 
		if(intention.noun[i] == "moose" && (intention.noun[i+1] == "livingroom" || intention.noun[i+1] == "living")){intention.noun[i] = "mooseLR";return;}
		if(intention.noun[i] == "moose" && intention.noun[i+1] == "bedroom"){intention.noun[i] = "mooseBR";return;}
		if(intention.noun[i] == "moose" && intention.noun[i+1] == "porch"){intention.noun[i] = "mooseFP";return;}
		//BETH 
		if(intention.noun[i] == "beth" && (intention.noun[i+1] == "livingroom" || intention.noun[i+1] == "living")){intention.noun[i] = "bethLR";return;}
		if(intention.noun[i] == "beth" && intention.noun[i+1] == "bedroom"){intention.noun[i] = "bethBR";return;}
		if(intention.noun[i] == "beth" && intention.noun[i+1] == "porch"){intention.noun[i] = "bethFP";	return;}
		//OTHER STUFF
		if(intention.noun[i] == "trevor" && intention.noun[i+1] == "trevWallet"){intention.noun[i] = "trevWallet";return;}
		if(intention.noun[i] == "love" && intention.noun[i+1] == "note"){intention.noun[i] = "loveNote";return;}
		if(intention.noun[i] == "autopsy" && intention.noun[i+1] == "report"){intention.noun[i] = "autopsy";return;}
		// make combiner for pill bottle?	
		if(intention.noun[i] == "model" && intention.noun[i+1] == "figurines"){intention.noun[i] = "figurines";return;}
		if(intention.noun[i] == "pharmacy" && intention.noun[i+1] == "receipt"){intention.noun[i] = "receipt";return;}		
		
	}
	return;
	
}

void action(struct Intent & intention, gamePkg *mybundle) {
	vector<string> roomNameVector = {"fake","bar","hidden", "police","morgue","pharmacy", "bobLR", 
						"bobOFF","bobBR","bobFP","claireLR","claireBUNK","claireBR",
						"claireFP","bethLR","bethBR", "bethFP","samLR", "samBR","samFP",
						"trentLR", "trentBR","trentFP","mooseLR","mooseBR","mooseFP"};
	bool isIntent = false;
	bool emptyVerbGoNoun = true;
    DEBUG_PRINT_LN if(intention.noun.size() > 0){cout << "intention.noun[0]: " << intention.noun[0] << endl;}
	DEBUG_PRINT_LN cout << "player current room is :" << (mybundle->thePlayer.getCurrentRoom())->getName() << endl; // did not change...
    shared_ptr<Room> current = mybundle->thePlayer.getCurrentRoom();												// get current room object
    DEBUG_PRINT_LN cout << "current room acquried from thePlayer: " << current->getName() << endl;
	shared_ptr<Object> roomObj;	
	if(intention.noun[0] != "none"){roomObj = find(current->myObjects, intention.noun[0]);}		// if noun is object in room, will return * or give null
    DEBUG_PRINT_LN cout << "room object acquisition attempt" << endl;
	shared_ptr<Character> roomChar;
	if(intention.noun[0] != "none"){roomChar = find(current->myPeople, intention.noun[0]);}	// if noun is character in room, will return * or give null
    DEBUG_PRINT_LN cout << "roomChar acquisition attempt" << endl;
	DEBUG_PRINT_LN cout << "verb enumeration is: " << intention.verbEnumType[0] << endl;
	
	for(int q = 0; q < intention.verb.size(); q++){
		if (intention.verb[q] != "none"){
			emptyVerbGoNoun = false;
		}
	}
		if(emptyVerbGoNoun){
			for(int z = 0; z < roomNameVector.size(); z++){
				if (roomNameVector[z] == intention.noun[0]){
					intention.verbEnumType.push_back(1);
				}
			}
		}
	
	switch (intention.verbEnumType[intention.verbEnumType.size() - 1]) {
	case ELSEIT:
		return;
		
	case go:
		//check that desired room isn't current room
        DEBUG_PRINT_LN	cout << "in the go part of the switch" << endl;

		if (current->getName() == intention.noun[0]) {
			std::cout << endl << "You are already here." << std::endl;
		}
		
		else{
			shared_ptr<Room> desiredRoom;
			desiredRoom = find(mybundle->theRooms, intention.noun[0]);
			DEBUG_PRINT_LN cout << "we have : " << intention.noun[0] << " and " << mybundle->theRooms[0]->getName() << endl;
			
			std::string direction;
			for(int i = 0; i < intention.verb.size(); i ++){
				if (intention.verb[i] == "north"){
					direction = "north";
				}
				else if (intention.verb[i] == "south"){
					direction = "south";
				}
				else if (intention.verb[i] == "east"){
					direction = "east";
				}
				else if (intention.verb[i] == "west"){
					direction = "west";
				}
				else{
					direction = "none";
				}
				
			}	
			for (int t = 0; t < intention.noun.size(); t++){
				if (intention.noun[t] != "none"){
					isIntent = true;
				}
			}
			if (!isIntent && direction == "none"){
				cout << "Please indicate as to WHERE you would like to go." << endl;
				return;
			}

			DEBUG_PRINT_LN cout << "PRE Lock Check" << endl;
			if(direction != "none"){
				desiredRoom = find(mybundle->theRooms,(current->getRoom(direction))->getName());
			}
				bool locked = false;
				for (int i = 0; i < current->myObjects.size(); i++){
					DEBUG_PRINT_LN cout << "PRE isLocked Loop" << endl;
					if (current->myObjects[i]->isLocked == true){
						DEBUG_PRINT_LN cout << "PRE getName()" << endl;
						string roomName = desiredRoom->getName();
						if(roomName == "bethLR" || roomName == "bobLR" || roomName == "samLR" || roomName == "mooseLR" || roomName == "claireLR" || roomName == "trentLR" || roomName == "claireBUNK" || roomName == "hidden"){
							if(current->getName() != "samBR"){
								cout << "The door is locked.." << endl;
								return;
							}
						}
					}
				}
			
			DEBUG_PRINT_LN cout << "POST Lock Check" << endl;				
			
			DEBUG_PRINT_LN cout << "desiredRoom is set to: " << desiredRoom->getName() << endl;
			if (desiredRoom == nullptr) {
				return;
			}

						
			if (desiredRoom->getName() == current->getRoom("north")->getName() && (direction == "north" || direction == "none")) {
				if (current->getRoom("north")->getName() == "fake")
					cout << endl << "There is nothing to the north.." << endl;
				else {
					//change player's current room to new room
					mybundle->thePlayer.setCurrentRoom(desiredRoom);
					desiredRoom->enter();
					if (mybundle->thePlayer.currentRoom->getName() == "hidden")
						mybundle->thePlayer.setHiddenVisited(true);
				}					
			}
			else if (desiredRoom->getName() == current->getRoom("south")->getName() && (direction == "south" || direction == "none")) {
				if (current->getRoom("south")->getName() == "fake")
					cout << endl << "There is nothing to the south.." << endl;
				else {
					//change player's current room to new room
					mybundle->thePlayer.setCurrentRoom(desiredRoom);
					desiredRoom->enter();
					if (mybundle->thePlayer.currentRoom->getName() == "claireBUNK")
						mybundle->thePlayer.setBunkVisited(true);
				}					
			}
			else if (desiredRoom->getName() == current->getRoom("east")->getName() && (direction == "east" || direction == "none")) {
				if (current->getRoom("east")->getName() == "fake")
					cout << endl << "There is nothing to the east.." << endl;
				else {
					//change player's current room to new room
					mybundle->thePlayer.setCurrentRoom(desiredRoom);
					desiredRoom->enter();
				}					
			}
			else if (desiredRoom->getName() == current->getRoom("west")->getName() && (direction == "west" || direction == "none")) {
				if (current->getRoom("west")->getName() == "fake")
					cout << endl << "There is nothing to the west.." << endl;
				else {
					//change player's current room to new room
					mybundle->thePlayer.setCurrentRoom(desiredRoom);
					desiredRoom->enter();
				}					
			}
			else
				cout << endl << "You cannot travel directly to " << desiredRoom->getDisplayName() << " from " << current->getDisplayName() << endl;
		}
		break;

	case look:
		{
		//if just look, then call room's description based on ifVisitied
		bool isAt = false;
		for(int p = 0; p < intention.preposition.size(); p++){
			if(intention.preposition[p] == "at"){
			isAt = true;
			}
		}
		if(!isAt){
			std::cout << current->getLongDescription() << std::endl;
			break;
		}
		if(mybundle->thePlayer.isInInventory(intention.noun[0])){
			std::cout << (mybundle->thePlayer.getFromInventory(intention.noun[0]))->getLongDescription() << std::endl;
			return;
		}
		if(roomObj != nullptr){
			std::cout << roomObj->getLongDescription() << std::endl;
			}
		else if(roomChar != nullptr){
			std::cout << roomChar->getLongDescription() << std::endl;
			}
		else{
			std::cout << "There's nothing significantly observable." << std::endl;					
			}
		}
		break;
			
	case take:
		{
		// check Room.object's isValid
		if(current->hasObject(intention.noun[0])){
			int result = mybundle->thePlayer.addToInventory(roomObj);
				if(result == 1){
					cout << endl << roomObj->displayName << " has been successfully added to your inventory." << endl;
					current->removeObject(roomObj->getName());
				}
			}
			else if(mybundle->thePlayer.isInInventory(intention.noun[0])){
				cout << "You already have that silly." << endl;
			}else if(intention.noun[0] == "none"){
				cout << "As all-knowing as I, the GAME, try and be...I just can't tell what you want to take." << endl;
			}else{
				cout << endl << "That object is not here." << endl;}
		}
		break;

	case help:
		{
		// print list of valid verbs
		cout << endl << "The following is a list of valid verbs:" << endl;
		cout << "  Go: Navigate to different rooms/places" << endl;
		cout << "  Look: See the description of the current room" << endl;
		cout << "  Look at: Examine a specific object/character" << endl;
		cout << "  Take: If an object can be taken, adds to inventory" << endl;
		cout << "  Help: Displays this list" << endl;
		cout << "  Hint: Displays a hint for the current room" << endl;
		cout << "  Inventory: Displays a list of the Player's inventory" << endl;
		cout << "  Edit: Brings up ability to view, add, or remove from Suspect List" << endl;
		cout << "  Talk: Engages in Dialogue with Character" << endl;
		cout << "  Arrest: Accuse Character to end game" << endl;
		cout << "  Use: Interact with object" << endl;
		cout << "  Knock: Request entry into house/building" << endl;
		cout << "  Drop: Put item in inventory down at current room/location" << endl;
		cout << "  Save: Save game to file" << endl;
		cout << "  Load: Load game from file" << endl; 
		cout << "  Layout: Displays a map of the town" << endl; 
		}		
		break;
			
	case hint:
		{
		// call room's hint
		cout << endl << "People you can talk to: " << endl;
		current->listPeople();
		cout << endl << "Objects you can look at: " << endl;
		current->listObjects();
		cout << endl << "Objects you can take as evidence: " << endl;
		current->listTakeable();
		cout << endl << "Where you can go: " << endl;
		if (current->getRoom("north")->getName() != "fake") {
			if (current->getName() != "bar")
				cout << " - North: " << current->getRoom("north")->getDisplayName() << endl;
			else if (mybundle->thePlayer.hiddenVisited == true)
				cout << " - North: " << current->getRoom("north")->getDisplayName() << endl;
		}
		if (current->getRoom("south")->getName() != "fake") {
			if (current->getName() != "claireLR")
				cout << " - South: " << current->getRoom("south")->getDisplayName() << endl;
			else if (mybundle->thePlayer.bunkVisited == true)
				cout << " - North: " << current->getRoom("south")->getDisplayName() << endl;
		}
		if (current->getRoom("east")->getName() != "fake")
			cout << " - East:  " << current->getRoom("east")->getDisplayName() << endl;
		if (current->getRoom("west")->getName() != "fake")
			cout << " - West:  " << current->getRoom("west")->getDisplayName() << endl;
		}		
		break;

			
	case inventory:
		{
		// print player's inventory
		mybundle->thePlayer.listInventory();
		}		
		break;

			
	case talk:
		{
			if((mybundle->thePlayer.getCurrentRoom())->myPeople.size() == 0){
				cout << "Is talking to an empty room healthy? Maybe you should make sure nobody catches you doing that..." << endl;
				return;
			}
			if(roomChar != nullptr){
				roomChar->speak();
			}else{
				cout << "While you may think it's not weird to talk to anything but a real person, others may disagree..." << endl;
			}
		}		
		break;

			
	case arrest:
		{
			int ac = mybundle->thePlayer.getArrestCount();
			mybundle->thePlayer.setArrestCount(ac + 1);
			if (ac >= 3){
				cout << "While you may have felt that accusing everyone was a good idea, the local PD disagrees. You weren't brought on for basing your work off of " << endl;
				cout << "luck, but you are being removed from the case because of it. Perhaps you should rethink your career path." << endl;
				intention.verb[0] = "quit";
			}
			else if(intention.noun[0] == "cat"){
				cout << "Incredible...you are a true detective, having had a deep gut feeling that the cat had somehow orchestrated the events surrounding Bobby's murder." << endl;
				cout << "The cat stares at you with a burning hatred as officers cuff and escort it into a nearby cruiser. It would have almost gotten away with it if it wasn't for you meddling law enforcement agents" << endl;
				intention.verb[0] = "quit";
			}
			else if(mybundle->thePlayer.isInInventory("pillBottle")){ // change to pill bottle
				if (intention.noun[0] == "claire"){
					cout << "Job well done, Detective! With the evidence in hand, you had what you needed to make the arrest! A BOLO was issued for \nClaire, which resulted in her being";
					cout << "identified and brought into police custody as she attempted to leave town. It turns out, Claire was obsessed with Beth, and was threatened by the idea" << endl;
					cout << "that Bobby and Beth may soon wed, furthering Claire's distance from Beth greatly. Claire stole Bobby's pill refill, crushed it, and tricked Trent into putting" << endl;
					cout << "it in his drink, causing Bobby's to overdose. Trent was implicated by Claire, further backed by the vial found in the bar trash, and was subsequently arrested." << endl;
					intention.verb[0] = "quit";
				}
			}
			else{
				cout << "You make the arrest, however, without enough evidence the local Police Department are forced to release your suspect. The Captain is not happy." << endl;
				cout << "You have made " << ac + 1 << " failed arrest." << endl;
			}
		}		
		break;

			
	case use: 
		{
			if(intention.noun[0] == "lockpick"){
				if(mybundle->thePlayer.isInInventory("lockpick")){
					if(mybundle->thePlayer.isInInventory("warrant")){
						for(int i = 0; i < current->myObjects.size(); i++){
							if(current->myObjects[i]->isLocked == true){
								current->myObjects[i]->setIsLocked(false);
								cout << "You deftly pick the lock." << endl;
								return;
							}
						} cout << "There is nothing to unlock." << endl; return;
					}else{
						cout << "Detective...c'mon, you know better than that. Without a warrant the illegal search of private property not only \ndisallows evidence found therein to"
								"be admissible in court, but you also commited a crime yourself. I, the GAME, cannot \nin good conscience let you make that mistake. You can foul up in"
								"other ways, but this once I will keep you from going \ndown a path from which you may not return." << endl;
								return;
					}
				}
				else{cout << "You don't have the means to do that." << endl;}
			}
			else if(intention.noun[0] == "light"){
				cout << "You turn on the flashlight, revealing what is before you...and in some way, revealing the truth that is around you." << endl;
				if(current->getName() == "hidden"){
					cout << "You shine the light around the room, until you see at the floor of the shelving something partially sticking out.\nYou stoop down to see it is a wallet." << endl;
				}
			}
			// unique to desk and hidden room
			else if(intention.noun[0] == "code"){
				if(mybundle->thePlayer.isInInventory("code") && (mybundle->thePlayer.getCurrentRoom())->getName() == "samBR"){
					for(int i = 0; i < current->myObjects.size(); i++){
						if (current->myObjects[i]->isLocked == true){
							current->myObjects[i]->setIsLocked(false);
							cout << "You search Sam's computer, and after about 20 minutes you find some emails he had written to Beth, which paint Sam as \ndesperately in love with her.";
							cout << "You see Sam has a small wireless printer hooked up to his laptop, so you print out the emails. \nYou should take them." << endl;

							shared_ptr<Character> tempChar = find((mybundle->theRooms[CMOOSELR])->myPeople, "sam");
							tempChar->setHasTalkedTo(2);
							tempChar = find((mybundle->theRooms[CMORGUE])->myPeople, "frank");
							tempChar->setHasTalkedTo(2);
							return;
						}
					}cout << "Already been unlocked, buddy." << endl;
				}else{cout << "You don't have the code, buddy." << endl;}
			}
			else if(intention.noun[0] == "key"){
				if(mybundle->thePlayer.isInInventory("key")){
						for(int i = 0; i < current->myObjects.size(); i++){
							if(current->myObjects[i]->isLocked == true){
								current->myObjects[i]->setIsLocked(false);
								cout << "You unlock the hidden door." << endl;
								return;
							}
						} cout << "There is nothing to unlock." << endl; return;
				}
				else{
					cout << "You don't have the means to do that." << endl;
				}		
			}
			else{
				cout << "You can't think of any useful way to use that." << endl;
			}
		}		
		break;

	case knock:
		{
		string currentRoomName = current->getName();
		if(currentRoomName == "bethFP" || currentRoomName == "claireFP"){
			shared_ptr<Room> otherSide = current->getRoom("east");
			if(otherSide->myPeople.size() == 0){
				cout << "You wait a few minutes, but no one answers." << endl;
			}
			else{
				cout << otherSide->myPeople[0]->dialogue[0] << endl;
				cout << "(You hear a click from the door unlocking)" << endl; 
				for (int i = 0; i < current->myObjects.size(); i++){  
					if (current->myObjects[i]->isLocked == true){
						current->myObjects[i]->setIsLocked(false);
					}
				}
				
			}
		}
		else if(currentRoomName == "bobFP" || currentRoomName == "mooseFP" || currentRoomName == "claireFP" || currentRoomName == "samFP" || currentRoomName == "trentFP"){
			shared_ptr<Room> otherSide = current->getRoom("west");
			if(otherSide->myPeople.size() == 0){
				cout << "You wait a few minutes, but no one answers." << endl;
			}
			else{
				//otherSide->myPeople[0]->speak();
				cout << otherSide->myPeople[0]->dialogue[0] << endl;
				cout << "(You hear a click from the door unlocking)" << endl; 
				for (int i = 0; i < current->myObjects.size(); i++){
					if (current->myObjects[i]->isLocked == true){
						current->myObjects[i]->setIsLocked(false);
					}
				}				
			}
		}
		else{
			cout << "There is no need to knock." << endl;
		}
		
		}
		break;
			
	case drop:
		{
			// add object to Room's object array, remove object from player inventory
			bool doesHave = false;
			shared_ptr<Object> temp;
			for(int i = 0; i < mybundle->thePlayer.myObjects.size(); i++){
				if(mybundle->thePlayer.myObjects[i]->getName() == intention.noun[0]){
					temp = mybundle->thePlayer.myObjects[i];
					cout << endl << "You have successfully placed " << mybundle->thePlayer.myObjects[i]->displayName << " in " << current->displayName << endl;					
					mybundle->thePlayer.removeFromInventory(mybundle->thePlayer.myObjects[i]);
					doesHave = true;
				}
			}
			if(doesHave){
				current->addObject(temp); //current?
			}
			else if(intention.noun[0] == "none"){
				cout << "If you would like to drop anything in particular, please indicate that." << endl;
			}
			else{
				cout << endl << "You do not have that item.." << endl;
			}
		}
		break;
			
	case hack:
		{
			if(intention.noun[0] == "bobPhone" || intention.noun[0] == "laptop" || intention.noun[0] == "bunkDoor"){
				if(intention.noun[0] == "bobPhone"){ 
					if(mybundle->thePlayer.isInInventory("bobPhone")){
						for(int i = 0; i < mybundle->thePlayer.myObjects.size(); i++){
							if (mybundle->thePlayer.myObjects[i]->isLocked == true){
								mybundle->thePlayer.myObjects[i]->setIsLocked(false);
								cout << "Your inner Hacker takes control as your days of hactivism aren't far behind, your fingers rapidly working as if possessed. Within seconds, you break the code..." << endl;
								cout << "You search through Bobby's text messages and find some threatening messages from Moose." << endl;
							}
						}
					}
					else{cout << "You don't have the means to do that." << endl;}
				}
				if(intention.noun[0] == "laptop"){ 
					for(int i = 0; i < current->myObjects.size(); i++){
						if (current->myObjects[i]->isLocked == true){
							current->myObjects[i]->setIsLocked(false);
							cout << "Your inner Hacker takes control as your days of hactivism aren't far behind, your fingers rapidly working as if possessed. Within seconds, you break the code..." << endl;
							cout << "You search Sam's computer, and after about 20 minutes you find some emails he had written to Beth, which paint Sam as desperately in love with her." << endl;
							cout << "You see Sam has a small wireless printer hooked up to his laptop, so your print out the emails." << endl;
							shared_ptr<Character> tempChar = find((mybundle->theRooms[CMOOSELR])->myPeople, "sam");
							tempChar->setHasTalkedTo(2);
							tempChar = find((mybundle->theRooms[CMORGUE])->myPeople, "frank");
							tempChar->setHasTalkedTo(2);
							return;
						}
					}
					cout << "No need, it's already unlocked my friend." << endl;
				}
				if(intention.noun[0] == "bunkDoor"){ 
					for(int i = 0; i < current->myObjects.size(); i++){
						if (current->myObjects[i]->isLocked == true){
							current->myObjects[i]->setIsLocked(false);
							cout << "Your inner Hacker takes control as your days of hactivism aren't far behind, your fingers rapidly working as if possessed. Within seconds, you break the code..." << endl;
							break;
						}
					}
					{cout << "You don't have the means to do that." << endl;}
				}
			}else{cout << "As much as you wish you may and wish you might, you just can't do it." << endl;}
		}
		break;
		
	case drink: 
		{
			if(intention.noun[0] == "beer"){
				for (int i = 0; i < current->myObjects.size(); i++){
					if(current->myObjects[i]->getName() == "beer"){
						int cd = mybundle->thePlayer.getDrinkCount(); 
						mybundle->thePlayer.setDrinkCount(cd + 1);
						cout << "You take a sip...ahhh, refreshing. You take another sip, then another...next you know it you have chugged the whole bottle." << endl; 
						cout << "Are you sure this is a good idea?" << endl;
						
						if(cd >= 3){
							cout << "Well now you've done it...you gone and got yourself drunk on the job. While these shenanigans may have worked back home," << endl;
							cout << "here they can't be hidden. You've outraged the local Police Department, who have removed you from the case and sent you packing." << endl;
							cout << "You spend the night in the drunk tank, contemplating what is assuredly a suspension if not a loss of employment. Are you happy with yourself?" << endl;
							intention.verb[0] = "quit";
						}
						return;
					}
				}
				cout << "There isn't any booze here." << endl;
			}else{
				cout << "You think long and hard about doing that, and just as you are about to try you decide that in this case, imagining the attempt will suffice." << endl;
			}
		}
		break;		
			
	case insight: // JESS AND AARON APPROVED
		{	
			if(intention.noun[0] == "none"){
				cout << "Is there anthing in particular you would like to get insightful about?" << endl;
				return;
			}else if(roomObj == nullptr){
				if(mybundle->thePlayer.isInInventory(intention.noun[0])){
					bool insight = mybundle->thePlayer.getFromInventory(intention.noun[0])->getInsight();
					if(insight){
						cout << "Oh yeah, in some way, shape, or form this object has something to do with progressing through the game. Something, my friend...something." << endl;
					}else{
						cout << "This object carries no game-changing weight. No need to waste your time with it." << endl; 
						cout << "You can if you want...really, just, you can turn your attention elsewhere to save time." << endl; 
						cout << "No obligations though. You are your own person, afterall. Please don't quit." << endl;
						}				
					return;
				}else{
				cout << "That thing isn't present to be insightful about." << endl;
				}
			}else{
				bool insight = roomObj->getInsight();
				if(insight){
					cout << "Oh yeah, in some way, shape, or form this object has something to do with progressing through the game. Something, my friend...something." << endl;
				}else{
					cout << "This object carries no game-changing weight. No need to waste your time with it." << endl; 
					cout << "You can if you want...really, just, you can turn your attention elsewhere to save time." << endl; 
					cout << "No obligations though. You are your own person, afterall. Please don't quit." << endl;
				}
			}
		}
		break;

	case edit:
		{
			string choice, person;
			bool validPerson = false;
			do{
			cout << "\nEnter 'list' to see current suspect list" << endl;
			cout << "Enter 'add' to add a name to the suspect list." << endl;
			cout << "Enter 'remove' to remove a name to the suspect list." << endl;	
			cout << "Enter 'quit' if you want to back out of this." << endl;
			getline (cin,choice);
			if(!(choice == "add" || choice == "remove" || choice == "quit" || choice == "list")){cout << "Please enter either 'list', 'add', 'remove', or 'quit'." << endl;}
			}while(!(choice == "add" || choice == "remove" || choice == "quit" || choice == "list"));
			if(choice == "quit"){break;}
			if(choice == "list"){mybundle->thePlayer.listSuspects(); break;}
			cout << "What is the name of the individual?" << endl;
			getline (cin,person);
			if(person[0] < 'a'){
				person[0] += 32;
			}
			for(int i = 0; i < mybundle->theChars.size(); i++){
				DEBUG_PRINT_LN cout << "We have: " << mybundle->theChars[i]->getName() << " and: " << person << "." << endl;
				if((mybundle->theChars[i]->getName()).compare(person) == 0){
					validPerson = true;
				}
			}
			person[0] -= 32;   
			DEBUG_PRINT_LN cout << validPerson << endl;
			if(validPerson && (choice == "add")){
				mybundle->thePlayer.addToSuspects(person);
				mybundle->thePlayer.listSuspects();
			}
			else if(validPerson && (choice == "remove")){
				mybundle->thePlayer.removeFromSuspects(person);
				mybundle->thePlayer.listSuspects();
			}			
			else{
				cout << "Are you sure that is relevant?" << endl;
			}
		}
		break;
		
		case layout:
		{
			//print map
			string line;
			ifstream myfile;
			
			if (mybundle->thePlayer.hiddenVisited == true && mybundle->thePlayer.bunkVisited == true)
				myfile.open ("map_w_all.txt");
			else if (mybundle->thePlayer.hiddenVisited == true && mybundle->thePlayer.bunkVisited == false)
				myfile.open ("map_w_hidden.txt");
			else if (mybundle->thePlayer.hiddenVisited == false && mybundle->thePlayer.bunkVisited == true)
				myfile.open ("map_w_bunk.txt");
			else 
				myfile.open ("map_w_none.txt");
			
			if (myfile.is_open()) {
				while ( getline (myfile,line) ) {
					cout << line << '\n';
				}
				myfile.close();
				cout << endl;
			}
			else cout << "Unable to display map";	
		}
		break;
		
		
	default:
		{
		cout << "error in verb enumeration" << endl;
		break;
			
		}
	}
}

shared_ptr<Room> find(vector<shared_ptr<Room>> s, std::string name){

	int cSize = s.size();
	for (int i = 0; i < cSize; i++) {
		DEBUG_PRINT_LN cout << "In find() we have: " << (s[i])->getName() << " and " << name << endl;
		if (name.compare((s[i])->getName()) == 0){ 
			DEBUG_PRINT_LN cout << i << endl;
			shared_ptr<Room> temp = s.at(i);
			return temp;
		}
	}
	//return nullptr;
	return static_cast<shared_ptr<Room>>(nullptr);
}

shared_ptr<Character> find(vector<shared_ptr<Character>> s, std::string name){
	int cSize = s.size();
	for (int i = 0; i < cSize; i++) {
		if ((s[i])->getName() == name) {
			shared_ptr<Character> temp = s[i];
			return temp;
		}
	}
	//return nullptr;
	return static_cast<shared_ptr<Character>>(nullptr);
}

shared_ptr<Object> find(vector<shared_ptr<Object>> s, std::string name){
	int cSize = s.size();
	for (int i = 0; i < cSize; i++) {
		DEBUG_PRINT_LN cout << "In find() we have: " << (s[i])->getName() << " and " << name << endl;
		if ((s[i])->getName() == name) { 
			shared_ptr<Object> temp = s[i];
			return temp;
		}
	}
	//return nullptr;
	return static_cast<shared_ptr<Object>>(nullptr);
}