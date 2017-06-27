/*********************************************************************
** Program Filename: Medusa.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Medusa subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from Medusa
*********************************************************************/

#include "Medusa.h"


/*********************************************************************
** Function: default constructor
** Description: creates medusa object, sets armor, strength, and
**	name to 3, 8, Medusa respectively
** Paramters: None
*********************************************************************/
Medusa::Medusa()
{
	six_sided_die = new Die(6);
	setArmor(3);
	setStrength(8);
	setName("Medusa");
}

/*********************************************************************
** Function: destructor
** Description: deletes 6-sided die created for medusa to roll
** Paramters: None
*********************************************************************/
Medusa::~Medusa()
{
	delete six_sided_die;
}


/*********************************************************************
** Function: attack
** Description: rolls 2 6-sided die and returns their sum as attack
**	damage. if sum = 12, uses glare attack and opponent dies.
** Parameters: none
** Pre-Conditions: players have been selected
** Post-Conditions: returns attack damage value
*********************************************************************/
int Medusa::attack()
{
	/* 2d6 attack */
	int attack_damage = six_sided_die->roll() + six_sided_die->roll();

	/* medusa glare attack: if medusa rolls a 12, opponent is turned to stone */
	if (attack_damage == 12)
	{
		cout << "Medusa Glares at her opponent." << endl;
		return 99;
	}

	else
	{
		cout << "Medusa's attack:   " << attack_damage << endl;
		return attack_damage;
	}
}

/*********************************************************************
** Function: defend
** Description: calculates and returns defense value after rolling 1
**	6-sided die and adding armor. also checks whether medusa is
**	dead or should continue to next round and if other medusa glared
** Parameters: value of incoming attack from other player
** Pre-Conditions: the int passed is valid
** Post-Conditions: returns result of combat and adjusts strength
*********************************************************************/
void Medusa::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{  
		cout << "Medusa has been turned to stone!" << endl;
		strength = 0;
	}

	else 
	{
		int damage = 0;
		int defense = 0;

		/* 1d6 defense + armor */
		defense = six_sided_die->roll() + armor;
		cout << "Medusa's defense: " << defense << endl;

		/* subtract defense from attack damage */
		damage = attack_damage - defense;

		/* damage cannot be negative */
		if (damage < 0)
		{
			damage = 0;
		}

		cout << endl << "Attack total damage: " << damage << " strength points."
			<< endl;

		/* subtract damage from strength */
		strength -= damage;

		/* strength cannot be negative */
		if (strength < 0)
		{
			strength = 0;
		}

		cout << endl << "Medusa is left with " << strength << " strength points."
			<< endl << endl;
	}
}