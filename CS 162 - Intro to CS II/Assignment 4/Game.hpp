/*********************************************************************
** Program Filename: Game.hpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Game class header file
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Queue.hpp"
#include "Stack.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Medusa.hpp"
#include "Barbarian.hpp"
#include "Vampire.hpp"
#include "BlueMen.hpp"
#include "HarryPotter.hpp"

class Game
{
public:
	int perTeam;       
	int team1players;          
	int team2players;          
	int rounds;              
	bool showData;       
	bool showLoss;          
	char lp;                 
	Queue *team1;              
	Queue *team2;               
	Stack *losers;           
	Creature *player1;      
	Creature *player2;      

	Game();
	Game(int, bool);
	~Game();

	void init();
	void setTeam(int);
	void play();
	void p1attack();
	void p2attack();
	void showLosers();

	/* accessors */
	int getPerTeam();
	bool getShowData();
	int getRounds();

	/* mutators */
	void setPerTeam(int);
	void setShowData(bool);
	void setRounds(int);
};

#endif