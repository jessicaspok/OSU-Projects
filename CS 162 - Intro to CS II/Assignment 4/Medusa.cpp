/*********************************************************************
** Program Filename: Medusa.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Medusa subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from Medusa
*********************************************************************/

#include "Medusa.hpp"

/*********************************************************************
** Function: constructor
** Description: creates medusa object, sets armor, strength, and
**	name to 3, 8, Medusa respectively
** Paramters: None
*********************************************************************/
Medusa::Medusa(string n, bool s)
{
	six_sided_die = new Die(6);
	setArmor(3);
	setstrength(8);
	setPoints(0);
	setName(n);
	setType("Medusa");
	setShowData(s);
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
		if (showData)
		{
			cout << "Medusa " << name << " glares at her opponent." << endl;
		}
		
		return 99;
	}

	else
	{
		if (showData)
		{
			cout << "Medusa " << name << "'s attack:   " << attack_damage << endl;
		}

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
int Medusa::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{
		if (showData)
		{
			cout << "Medusa " << name << "  has been turned to stone!" << endl;
		}

		strength = 0;
		return 20;
	}

	else 
	{
		/* 1d6 defense + armor */
		int defense = six_sided_die->roll() + armor;
		int p1pts = defensePrint(name, type, attack_damage, defense);
		return p1pts;
	}
}

/*********************************************************************
** Function: recover
** Description: fighter regains half of their strength
** Parameters: none
** Pre-Conditions: creature is alive
** Post-Conditions: adjusts strength
*********************************************************************/
void Medusa::recover()
{
	int life = strength + 4;
	
	if (life > 8)
	{
		strength = 8;
	}

	else
	{
		strength = life;
	}
}