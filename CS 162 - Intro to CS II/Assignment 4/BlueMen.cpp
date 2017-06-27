/*********************************************************************
** Program Filename: BlueMen.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: BlueMen subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from Blue Men
*********************************************************************/

#include "BlueMen.hpp"

/*********************************************************************
** Function: constructor
** Description: creates Blue Men object, sets armor, strength, and
**	name to 3, 12, The Blue Men respectively
** Paramters: None
*********************************************************************/
BlueMen::BlueMen(string n, bool s)
{
	six_sided_die = new Die(6);
	ten_sided_die = new Die(10);
	setArmor(3);
	setstrength(12);
	setPoints(0);
	setName(n);
	setType("The Blue Men");
	setShowData(s);	
}

/*********************************************************************
** Function: destructor
** Description: deletes 6-sided and 10-sided die created for blue men
**	to roll
** Paramters: None
*********************************************************************/
BlueMen::~BlueMen()
{
	delete six_sided_die;
	delete ten_sided_die;
}

/*********************************************************************
** Function: attack
** Description: rolls 2 10-sided die and returns their sum as attack
**	damage
** Parameters: none
** Pre-Conditions: players have been selected
** Post-Conditions: returns attack damage value
*********************************************************************/
int BlueMen::attack()
{
	int attack_damage = ten_sided_die->roll() + ten_sided_die->roll();

	if (showData)
	{
		cout << "The Blue Men " << name << "'s attack:   " << attack_damage << endl;
	}

	return attack_damage;
}

/*********************************************************************
** Function: defend
** Description: calculates and returns defense value after rolling
**	appropriate number of die factoring in the mob power and adding
**	armor. also checks whether blue men are dead or should continue
**	to next round and if medusaglared
** Parameters: value of incoming attack from other player
** Pre-Conditions: the int passed is valid
** Post-Conditions: returns result of combat and adjusts strength
*********************************************************************/
int BlueMen::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{
		if (showData)
		{
			cout << "The Blue Men " << name << " have been turned to stone!" << endl;
		}

		strength = 0;
		return 20;
	}
	else 
	{
		int defense;

		/* mob defense - for every 4 points of damage, lose 1 defense die */
		if (strength <= 4)
		{
			/* 1d6 + armor */
			defense = six_sided_die->roll() + armor;
		}
		else if (strength <= 8)
		{
			/* 2d6 + armor */
			defense = six_sided_die->roll() + six_sided_die->roll() + armor;
		}
		else if (strength <= 12)
		{
			/* 3d6 + armor */
			defense = six_sided_die->roll() + six_sided_die->roll() + six_sided_die->roll() + armor;
		}

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
void BlueMen::recover()
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