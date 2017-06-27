#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include "string.h"

#include "Game.h"
#include "gameLoader.hpp" 

using namespace std;

int main() {
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int rows = w.ws_row;
	int cols = w.ws_col;
	
	cout << "\e[1;31m \n \
                           _,   _, _ _,_ __, __, __, __,    _, ___   ___ _,_ __,   \n \
                          / \\   |\\/| | | |_) | \\ |_  |_)   /_\\  |     |  |_| |_\n \
                          |~|   |  | | | | \\ |_/ |   | \\   | |  |     |  | | |   \n \
                          ~ ~   ~  ~ `~' ~ ~  ~  ~~~ ~ ~   ~ ~  ~     ~  ~ ~ ~~~   \e[0m" << endl;

	cout << "\e[1;31m \
                          ___ _,_ _ __,  _, ___ , _   _  _ _,_ _  _, ___ _,  __,\n \
                           |  |_| | |_) (_   |  \\ |   |  | |_| | (_   |  |   |_ \n \
                           |  | | | | \\ , )  |   \\|   |/\\| | | | , )  |  | , |  \n \
                           ~  ~ ~ ~ ~ ~  ~   ~    )   ~  ~ ~ ~ ~  ~   ~  ~~~ ~~~\n \
                                                 ~'                              \n\e[0m" << endl;
										
	Game* currentGame = new Game;
	gamePkg *thisBundle;
	
	// display menu for either load game or new game
	if (rows > 29 && cols > 119) {
		do{
			cout << "To start a new game, type: new game" << endl;
			cout << "To load a saved game, type: load game" << endl;
			cout << "To delete a saved game, type: del game" << endl;
			cout << "To repair corrupted game file, type: gen game"<< endl;			
			cout << "Or, to quit the game, type: quit" << endl;
		
			string start;
			getline (cin, start);
		
			// create the classes and files
			if (start[0] == 'g' || start[0] == 'G') {
				// Initialize a new game
				 currentGame->generate();
			}
			if (start[0] == 'n' || start[0] == 'N') {
				// Initialize a new game
				cout << endl << "There's been a murder in Small Town, U.S.A., and the STPD needs your help. Bobby had so much to live for and the whole" << endl
					<< "town is still shocked by his gruesome murder. To figure out whodunit, collect clues and talk to residents around town." << endl
					<< "The first responders have already taken care of his body and sent it down to the Morgue. They've also taken the liberty" << endl
					<< "of jotting down all the residents' names for you so you can cross people off your suspect list when you're sure they " << endl
					<< "didn't do it. Once you have gathered enough evidence to pinpoint the murderer, arrest him/her and if you're correct, " << endl
					<< "you'll be crowned a local hero. If you get stuck, type in 'hint' or 'help' for clues." << endl << endl
					<< "Good luck to you, detective- you're gonna need it..." << endl << endl;
				thisBundle = currentGame->initGame();
				break;
			}
			else  if (start[0] == 'l' || start[0] == 'L'){
				// load a saved game
				cout<<"load a saved game"<<endl;
				thisBundle = currentGame->loadGame("");
				if(thisBundle != NULL)
					break;
			}
			else  if (start[0] == 'd' || start[0] == 'D'){
				// delete a saved game
				cout<<"delete a saved game"<<endl;
				currentGame->deleteGame();
			}
			else if (start[0] == 'q' || start[0] == 'Q') {
				// Quit
				cout << "Bye" << endl;
				return 0;
			}	
		  }while(true);
		  
		  thisBundle = currentGame->runGame(thisBundle);
	}
	else {
		cout << endl << endl << "Please increase your terminal window size to play the game!!" 
			<< endl << endl << "Your current window size is " << rows << " rows by " << cols 
			<< " columns" << endl << "We require the window to be 30 rows by 120 columns (at least) " 
			<< endl << endl << "Why are you trying to play in such a small window, anyway?" << endl
			<< "There's no way you have anything cooler open..." << endl << endl << endl;
	}
	
	return 0;
	
}