/****************************************************************************************
** Class file: Game.hpp
** Author: Jessica Spokoyny
** Date: 02/28/162-28-16
** Description: Creates and runs a fighting tournament between various Creature derived
**              objects. Winners and losers(optional) are displated at the end.
****************************************************************************************/

#include "Game.hpp"
#include <ctime>

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
** Description: creates a Game with two teams
** Paramters: int, bool
*********************************************************************/
Game::Game(int p, bool showData)
{
	this->perTeam = p;
	this->team1players = p;
	this->team2players = p;
	this->showData = showData;

	/* seed random number generator */
	srand(time(NULL));
}

/*********************************************************************
** Function: destructor
** Description: deletes both teams and losers
** Paramters: None
*********************************************************************/
Game::~Game()
{
	delete team1;
	delete team2;
	delete losers;
}

/*********************************************************************
** Function: init
** Description: creates the 3 lists for winners and losers, prompts
**	user for players
** Parameters: none
*********************************************************************/
void Game::init()
{
	team1 = new Queue;
	team2 = new Queue;
	losers = new Stack;

	/* prompt user to select players */
	setTeam(1);
	setTeam(2);

}

/*********************************************************************
** Function: setTeam
** Description: fills teams with players
** Parameters: int
*********************************************************************/
void Game::setTeam(int teamNum)
{
	int choice;        
	string tempName;     
	Creature *tempC = 0;   

	/* for each player on the team, select type and name */
	for (int i = 0; i < perTeam; i++)
	{
		system("clear");

		cout << "Please select Player " << i + 1 << " for Team " << teamNum
			<< "." << endl << endl << " 1: Medusa" << endl << " 2: Barbarian"
			<< endl << " 3: Vampire" << endl << " 4: Blue Men" << endl
			<< " 5: Harry Potter" << endl << endl;

		cin >> choice;

		/* input validation */
		while (choice < 1 || choice > 5)
		{
			cout << "Please choose a number from 1 - 5." << endl;
			cin >> choice;
		}

		cout << "Please enter the name of Player " << i + 1 << ":" << endl;
		cin.ignore();
		getline(cin, tempName);

		/* create new player */
		if (choice == 1)
		{
			tempC = new Medusa(tempName, showData);
		}
		else if (choice == 2)
		{
			tempC = new Barbarian(tempName, showData);
		}
		else if (choice == 3)
		{
			tempC = new Vampire(tempName, showData);
		}
		else if (choice == 4)
		{
			tempC = new BlueMen(tempName, showData);
		}
		else if (choice == 5)
		{
			tempC = new HarryPotter(tempName, showData);
		}

		/* add to queue */
		if (teamNum == 1)
		{
			team1->add(tempC);
		}
		else 
		{
			team2->add(tempC);
		}
	}
}

/*********************************************************************
** Function: play
** Description: starts the match, prints winner of tournament
** Parameters: int type of creature
*********************************************************************/
void Game::play()
{
	/* if both teams have players alive */
	do {
		/* get players from queues */
		player1 = team1->getFront()->data;
		team1->remove();

		player2 = team2->getFront()->data;
		team2->remove();

		system("clear");
		if (showData){
			cout << "---------------------------------------" << endl;
			cout << "Round " << rounds + 1 << " :  " << player1->getType() << " "
				<< player1->getName() << "   Vs.   " << player2->getType()
				<< " " << player2->getName() << endl;
			cout << "---------------------------------------" << endl << endl;
		}

		/* first player attacks */
		p1attack();
	} while ((team1->getFront() != NULL) && (team2->getFront() != NULL));

	system("clear");
	/* Team 2 won */
	if (team1->getFront() == NULL)
	{
		cout << "  - Team 2 won the tournament! -" << endl << endl;
		team2->print();
		showLosers();
	}

	/* Team 1 won */
	else 
	{ 
		cout << "  - Team 1 won the tournament! -" << endl << endl;
		team1->print();
		showLosers();
	}
}

/*********************************************************************
** Function: p1Attack
** Description: p1 attacks p2
** Parameters: 
*********************************************************************/
void Game::p1attack()
{
	/* p1 attacks and p2 defends*/
	int attack_damage = player1->attack();
	int pts = player2->defend(attack_damage);
	
	/* add points based on damage inflicted */
	player1->addPoints(pts);

	if (showData && pts > 0)
	{
		cout << player1->getType() << " " << player1->getName() << " earned " << pts << " points.";
	}
	cout << endl << endl;

	/* p2 killed */
	if (player2->getstrength() == 0)
	{
		if (showData)
		{
			cout << endl << "---------------------------------------" << endl << endl;
			cout << player2->getType() << " " << player2->getName()
				<< " has been killed.." << endl << endl;

			cout << "Team 1 has " << team1players << " players left." << endl;
			cout << "Team 2 has " << --team2players << " players left." << endl;

			cout << player1->getType() << " " << player1->getName()
				<< " had " << player1->getstrength()
				<< " strength points remaining." << endl << endl;
		}

		/* p2 added to loser stack, p1 added to queue */
		losers->add(player2);
		player1->recover();
		team1->add(player1);

		/* next round */
		rounds++;

		if (showData)
		{
			cout << endl << "Press Enter to continue.. " << endl;
			cin.get();
		}
	}

	/* p2 attacks p1 */
	else
		p2attack();
}

/*********************************************************************
** Function: p2Attack
** Description: p2 attacks p1
** Parameters:
*********************************************************************/
void Game::p2attack()
{
	/* p2 attacks and p1 defends*/
	int attack_damage = player2->attack();
	int pts = player1->defend(attack_damage);

	/* add points based on damage inflicted */
	player2->addPoints(pts);

	if (showData && pts > 0)
	{
		cout << player2->getType() << " " << player2->getName() << " earned " << pts << " points.";
	}
	
	cout << endl << endl;

	/* p1 killed */
	if (player1->getstrength() == 0)
	{
		if (showData)
		{
			cout << "---------------------------------------" << endl << endl;
			cout << player1->getType() << " " << player1->getName()
				<< " has been killed.." << endl;

			cout << "Team 1 has " << --team1players << " players left." << endl;
			cout << "Team 2 has " << team2players << " players left." << endl;

			cout << player2->getType() << " " << player2->getName()
				<< " had " << player2->getstrength()
				<< " strength points remaining." << endl << endl;
		}

		/* p1 added to loser stack, p2 added to queue */
		losers->add(player1);
		player2->recover();
		team2->add(player2);

		/* next round */
		rounds++;

		if (showData)
		{
			cout << "Press Enter to continue.. " << endl;
			cin.get();
		}
	}

	/* p1 attacks p2 */
	else
		p1attack();
}

/*********************************************************************
** Function: showLosers
** Description: prompt user to show losers, if yes, call print fxn
** Parameters: none
*********************************************************************/
void Game::showLosers()
{
	/* prompt to show losers */
	cout << "Would you like to see the losing players? (y/n): ";
	cin >> lp;

	/* input validation */
	while ((lp != 'y' && lp != 'Y') && (lp != 'n' && lp != 'N'))
	{
		cout << "Please enter y or n: ";
		cin >> lp;
	}

	/* show losers */
	if (lp == 'y' || lp == 'Y')
	{
		losers->print();
	}

	/* return to menu */
	cout << "Press Enter to play again." << endl;
	cin.ignore();
	cin.get();
}

/*********************************************************************
** Function: getPerTeam
** Description: returns players per team
** Parameters: none
*********************************************************************/
int Game::getPerTeam()
{
	return perTeam;
}

/*********************************************************************
** Function: getShowData
** Description: returns t/f
** Parameters: none
*********************************************************************/
bool Game::getShowData()
{
	return showData;
}

/*********************************************************************
** Function: getRounds
** Description: returns number of rounds
** Parameters: none
*********************************************************************/
int Game::getRounds()
{
	return rounds;
}

/*********************************************************************
** Function: setPerTeam
** Description: set number of players per team
** Parameters: int
*********************************************************************/
void Game::setPerTeam(int n)
{
	this->perTeam = n;
}

/*********************************************************************
** Function: setShowData
** Description: set t/f
** Parameters: bool
*********************************************************************/
void Game::setShowData(bool d)
{
	this->showData = d;
}

/*********************************************************************
** Function: setRounds
** Description: set number of rounds
** Parameters: int
*********************************************************************/
void Game::setRounds(int r)
{
	this->rounds = r;
}
