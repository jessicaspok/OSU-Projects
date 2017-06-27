/*********************************************************************
** Program Filename: Game.h
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Game class header file
*********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "Die.h"
#include "Creature.h"

class Game
{
private:
	int rounds;         
	int p1;                 
	int p2;                
	Creature *Player1;   
	Creature *Player2;     

public:
	Game();
	Game(int, int);
	~Game();

	void setPlayers();
	void play();

	void p1attack();
	void p2attack();

	/* accessors */
	int getP1();
	int getP2();

	/* mutators */
	void setP1(int);
	void setP2(int);

};

#endif