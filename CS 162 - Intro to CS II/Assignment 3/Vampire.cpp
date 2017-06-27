/*********************************************************************
** Program Filename: Vampire.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Vampire subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from Vampire, or text if used charm
*********************************************************************/

#include "Vampire.h"

/*********************************************************************
** Function: default constructor
** Description: creates vampire object, sets armor, strength, and
**	name to 1, 18, The Vampire respectively
** Paramters: None
*********************************************************************/
Vampire::Vampire()
{
	six_sided_die = new Die(6);
	twelve_sided_die = new Die(12);
	setArmor(1);
	setStrength(18);
	setName("The Vampire");
}

/*********************************************************************
** Function: destructor
** Description: deletes 6-sided die created for vampire to roll
** Paramters: None
*********************************************************************/
Vampire::~Vampire()
{
	delete six_sided_die;
	delete twelve_sided_die;
}

/*********************************************************************
** Function: attack
** Description: rolls 1 12-sided die and returns that value as attack
**	damage
** Parameters: none
** Pre-Conditions: players have been selected
** Post-Conditions: returns attack damage value
*********************************************************************/
int Vampire::attack()
{
	/* 1d12 attack */
	int attack_damage = twelve_sided_die->roll();
	cout << "The Vampire's attack: " << attack_damage << endl;
	return attack_damage;
}

/*********************************************************************
** Function: defend
** Description: calculates and returns defense value after rolling 1
**	6-sided die and adding armor. also checks whether harry potter is
**	dead or should continue to next round and if medusa glared
** Parameters: value of incoming attack from other player
** Pre-Conditions: the int passed is valid
** Post-Conditions: returns result of combat and adjusts strength
*********************************************************************/
void Vampire::defend(int attack_damage)
{
	/* vampire charm: each attack has 50% chance of not occurring */
	int charm = rand() % 2;
	if (charm)
	{
		cout << "But, The Vampire charmed the opponent into not attacking!"
			<< endl << endl;
	}

	/* medusa glare attack */
	else if (attack_damage == 99)
	{  
		cout << "The Vampire has been turned to stone!" << endl;
		strength = 0;
	}
	
	else 
	{
		int damage = 0;
		int defense = 0;

		/* 1d6 defense + armor */
		defense = six_sided_die->roll() + armor;
		cout << "The Vampire's defense: " << defense << endl;

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

		cout << endl << "The Vampire is left with " << strength << " strength points." 
			<< endl << endl;
	}
}