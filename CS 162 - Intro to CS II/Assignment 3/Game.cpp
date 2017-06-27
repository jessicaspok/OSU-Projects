/*********************************************************************
** Program Filename: Game.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: game class implementation file
** Input: int values for type of creature for p1 and p2
** Output: status after each round, who dies, round numbers
*********************************************************************/

#include <ctime>
#include <cstdlib>
#include "Game.h"
#include "Medusa.h"
#include "Barbarian.h"
#include "Vampire.h"
#include "BlueMen.h"
#include "HarryPotter.h"

/*********************************************************************
** Function: default constructor
** Description: creates a Game
** Paramters: None
*********************************************************************/
Game::Game()
{
}

/*********************************************************************
** Function: constructor
** Description: creates a Game and sets the 2 players
** Paramters: int p1 and p2
*********************************************************************/
Game::Game(int p1, int p2)
{
	rounds = 1;

	setP1(p1);
	setP2(p2);

	/* seed random number generator */
	srand(time(NULL));
}

/*********************************************************************
** Function: destructor
** Description: deletes both players 
** Paramters: None
*********************************************************************/
Game::~Game()
{
	delete Player1;
	delete Player2;
}

/*********************************************************************
** Function: setPlayers
** Description: creates the 2 players selected by the user
** Parameters: none
*********************************************************************/
void Game::setPlayers()
{
	/* new player 1 */
	if (p1 == 1)
	{
		Player1 = new Medusa();
	}
	else if (p1 == 2)
	{
		Player1 = new Barbarian();
	}
	else if (p1 == 3)
	{
		Player1 = new Vampire();
	}
	else if (p1 == 4)
	{
		Player1 = new BlueMen();
	}
	else if (p1 == 5)
	{
		Player1 = new HarryPotter();
	}

	/* new player 2 */
	if (p2 == 1)
	{
		Player2 = new Medusa();
	}
	else if (p2 == 2)
	{
		Player2 = new Barbarian();
	}
	else if (p2 == 3)
	{
		Player2 = new Vampire();
	}
	else if (p2 == 4)
	{
		Player2 = new BlueMen();
	}
	else if (p2 == 5)
	{
		Player2 = new HarryPotter();
	}
}

/*********************************************************************
** Function: play
** Description: prints the initial strengths of the 2 players and 
**	starts the battle
** Parameters: none
*********************************************************************/
void Game::play()
{
	/* set players 1 and 2 according to user selection */
	setPlayers();
	system("clear");
	
	cout << "Player 1: " << Player1->getName() << " has " << Player1->getStrength()
		<< " Strength Points." << endl;
	cout << "Player 2: " << Player2->getName() << " has " << Player2->getStrength()
		<< " Strength Points." << endl;
	cout << "    ----------------------------------------" << endl;

	/* Player 1 to attack first */
	p1attack();

	cout << endl << "Press Enter to play again..." << endl;
	cin.ignore();
	cin.get();
}

/*********************************************************************
** Function: p1attack
** Description: player 1's attacks, p2 defends. If p2 survives, move
**	on to player 2's attack
** Parameters: none
*********************************************************************/
void Game::p1attack()
{
	cout << endl << "Round: " << rounds << endl << endl;

	/* initialize damage to 0 */
	int attack_damage = 0;

	/* call p1's attack function */
	attack_damage = Player1->attack();

	/* pass the attack damage to p2 and call p2's defend function */
	Player2->defend(attack_damage);

	/* if strength points <= 0, player 2 is out of combat */
	if (Player2->getStrength() <= 0)
	{
		cout << "    ----------------------------------------" << endl << endl;
		cout << "Player 2, " << Player2->getName() << " has died. "
			<< endl;
		cout << "Player 1, " << Player1->getName() << " still has " << Player1->getStrength()
			<< " strength points." << endl;
	}

	/* if not, call p2's attack function */
	else
	{
		p2attack();
	}
}

/*********************************************************************
** Function: p2attack
** Description: player 2's attacks, p1 defends. If p1 survives, move
**	on to player 1's attack
** Parameters: none
*********************************************************************/
void Game::p2attack()
{
	/* initialize damage to 0 */
	int attack_damage = 0;

	/* call p2's attack function */
	attack_damage = Player2->attack();

	/* pass the attack damage to p1 and call p1's defend function */
	Player1->defend(attack_damage);

	/* if strength points <= 0, player 1 is out of combat */
	if (Player1->getStrength() <= 0)
	{
		cout << "    ----------------------------------------" << endl << endl;
		cout << "Player 1: " << Player1->getName() << " has died."
			<< endl;
		cout << "Player 2: " << Player2->getName() << " still has " << Player2->getStrength()
			<< " strength points." << endl;
	}
	
	/* if both still have strength */
	else 
	{
		cout << "    ----------------------------------------" << endl;

		/* move on to next round */
		rounds++;

		/* player 1 to attack again */
		p1attack();
	}
}

/*********************************************************************
** Function: getP1
** Description: returns the type of creature in p1
** Parameters: none
*********************************************************************/
int Game::getP1()
{
	return p1;
}

/*********************************************************************
** Function: getP2
** Description: returns the type of creature in p2
** Parameters: none
*********************************************************************/
int Game::getP2()
{
	return p2;
}

/*********************************************************************
** Function: setP1
** Description: set p1 to type of creature passed in
** Parameters: int type of creature
*********************************************************************/
void Game::setP1(int p1)
{
	this->p1 = p1;
}

/*********************************************************************
** Function: setP2
** Description: set p2 to type of creature passed in
** Parameters: int type of creature
*********************************************************************/
void Game::setP2(int p2)
{
	this->p2 = p2;
}



