/*********************************************************************
** Program Filename: Barbarian.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: Barbarian subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from barbarian
*********************************************************************/

#include "Barbarian.h"

/*********************************************************************
** Function: default constructor
** Description: creates barbarian object, sets armor, strength, and
**	name to 0, 12, The Barbarian respectively
** Paramters: None
*********************************************************************/
Barbarian::Barbarian()
{
	six_sided_die = new Die(6);
	setArmor(0);
	setStrength(12);
	setName("The Barbarian");
}

/*********************************************************************
** Function: destructor
** Description: deletes 6-sided die created for barbarian to roll
** Paramters: None
*********************************************************************/
Barbarian::~Barbarian()
{
	delete six_sided_die;
}

/*********************************************************************
** Function: attack
** Description: rolls 2 6-sided die and returns their sum as attack
**	damage
** Parameters: none
** Pre-Conditions: players have been selected
** Post-Conditions: returns attack damage value
*********************************************************************/
int Barbarian::attack()
{
	/* 2d6 attack */
	int attack_damage = six_sided_die->roll() + six_sided_die->roll();
	cout << "The Barbarian's attack:   " << attack_damage << endl;
	return attack_damage;
}

/*********************************************************************
** Function: defend
** Description: calculates and returns defense value after rolling 2
**	6-sided die and adding armor. also checks whether barbarian is
**	dead or should continue to next round and if medusa glared
** Parameters: value of incoming attack from other player
** Pre-Conditions: the int passed is valid
** Post-Conditions: returns result of combat and adjusts strength
*********************************************************************/
void Barbarian::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{  
		cout << "The Barbarian has been turned to stone!" << endl;
		strength = 0;
	}
	else 
	{
		int damage = 0;
		int defense = 0;
		
		/* 2d6 defense + armor */
		defense = six_sided_die->roll() + six_sided_die->roll() + armor;
		cout << "The Barbarian's defense: " << defense << endl;

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

		cout << endl << "The Barbarian is left with " << strength << " strength points."
			<< endl << endl;
	}
}