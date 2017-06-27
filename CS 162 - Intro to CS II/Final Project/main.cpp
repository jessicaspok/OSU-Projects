#include <iostream>
#include <string>
#include <time.h>
#include "Player.hpp"
#include "Space.hpp"
#include "Bedroom.hpp"
/*********************************************************************
** Program Filename: main.cpp
** Author: Jessica Spokoyny
** Date: 03/13/16
** Description: main driver function for robbery escape game
*********************************************************************/
#include "Bathroom.hpp"
#include "Hallway.hpp"
#include "Kitchen.hpp"
#include "LivingRoom.hpp"

int main() 
{
	/* initialize spaces and choice vars */
	Player *p = new Player();
	Bedroom *bed = new Bedroom(p);
	Bathroom *bath = new Bathroom(p);
	Hallway *hall = new Hallway(p);
	Kitchen *kit = new Kitchen(p);
	LivingRoom *lr = new LivingRoom(p);

	/* start in bedroom */
	Space *currentRoom = bed;

	bed->addSpace(hall, NULL, NULL, NULL);
	bath->addSpace(hall, NULL, NULL, NULL);
	kit->addSpace(hall, lr, NULL, NULL);
	lr->addSpace(hall, kit, NULL, NULL);
	hall->addSpace(bed, bath, kit, lr);

	int userChoice = 0;
	int roomChoice = 0;
	time_t now, start;
	double seconds = 0;

	/* intro to game */
	cout << "********************** ROBBERY ESCAPE **********************" << endl 
		<< endl;
	cout << "You are a thief.. You have decided to break into the house of a "
		<< "rich man " << endl << "as he is said to possess many valuables. " << endl
		<< endl << "You break in through the chimney but you will "
		<< "need to find another way out." << endl << endl
		<< "Once you're inside, you see a pitbull. But if you keep quiet, it won't" 
		<< " attack." << endl << endl
		<< "You make your way into the bedroom and see a safe in the corner. "
		<< endl << "You don't know the code, but decide to try opening it anyway."
		<< endl << endl
		<< "Big mistake!! The safe set off a silent alarm - all of the windows and "
		<< "doors " << endl << "have been sealed and the police will arrive in 60 "
		<< "seconds!" << endl << endl << "You need to find a way out... quick!"
		<< endl << "And don't make too much noise.. or the dog will get you." << endl 
		<< endl;
	
	/* main menu */
	while (userChoice != 1)
	{
		cout << endl << "***********************************************"
			<< endl << " Main Menu "
			<< endl << "***********************************************"
			<< endl << "	Press 1 to start the game" 
			<< endl << "	Press 2 to see a clue" << endl;
		cin >> userChoice;

		if (userChoice == 2) 
		{
			cout << endl
				<< "Clue: All of the windows and doors have been locked." << endl
				<< "   In order to escape, you must find a way to unlock/break an exit"
				<< endl << endl << "   This can be done by: " << endl
				<< "	1. finding the key (to unlock the front door)" << endl
				<< "	2. finding the sledgehammer (to break a window)" << endl
				<< endl << "   But you only have 60 seconds to find a way out " 
				<< "   before you are caught!" << endl << endl;
		}		
	}

	/* start time */
	time(&start);                             

	/* continue game unless dog attack, escape, or time is up */
	while (roomChoice != 10 && roomChoice != 9 && seconds <= 60) 
	{
		roomChoice = currentRoom->option();

		if (roomChoice == 1 || roomChoice == 2 || roomChoice == 3 || roomChoice == 4) 
		{
			currentRoom = currentRoom->getSpace(roomChoice);
		}

		/* current time */
		time(&now);

		/* elapsed time */
		seconds = difftime(now, start);       
	}

	/* dog attacked */
	if (roomChoice == 9) 
	{
		cout << endl << "Womp Womp.. You Lose!" << endl;
	}

	/* player escaped */
	else if (roomChoice == 10)
	{
		cout << endl << "Woohoo.. You win! " << endl;
	}

	/* time ran out */
	else
	{
		cout << endl << "You took too long and the police have arrived."
			<< endl << endl << "Womp Womp.. You Lose!" << endl;
	}
}