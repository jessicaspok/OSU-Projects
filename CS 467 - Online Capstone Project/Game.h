#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <string>
#include <iostream>
#include "gameLoader.hpp" 
#include "parsing_module.hpp" 

using namespace std;

	
class Game {                  
public:
	Game();     
	void configGame(gamePkg *g);	
	gamePkg *runGame(gamePkg *);
	gamePkg *generate();
	gamePkg *initGame();                         
	gamePkg *loadGame(string);                    
	int saveGame(gamePkg *, string);
	void deleteGame();	
	void sandsOfTime(gamePkg *mybundle);
};
#endif