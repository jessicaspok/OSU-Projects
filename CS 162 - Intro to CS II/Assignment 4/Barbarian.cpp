/*********************************************************************
** Program Filename: Barbarian.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: Barbarian subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from barbarian
*********************************************************************/

#include "Barbarian.hpp"

/*********************************************************************
** Function: constructor
** Description: creates barbarian object, sets armor, strength, and
**	name to 0, 12, The Barbarian respectively
** Paramters: None
*********************************************************************/
Barbarian::Barbarian(string n, bool s)
{
	six_sided_die = new Die(6);
	setArmor(0);
	setstrength(12);
	setPoints(0);
	setName(n);
	setType("The Barbarian");
	setShowData(s);
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

	if (showData)
	{
		cout << "The Barbarian " << name << "'s attack:   " << attack_damage << endl;
	}

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
int Barbarian::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{  
		if (showData)
		{
			cout << "The Barbarian " << name << " has been turned to stone!" << endl;
		}

		strength = 0;
		return 20;
	}
	else 
	{
		/* 2d6 defense + armor */
		int defense = six_sided_die->roll() + six_sided_die->roll() + armor;
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
void Barbarian::recover()
{
	int life = strength + 6;

	if (life > 12)
	{
		strength = 12;
	}

	else
	{
		strength = life;
	}
}