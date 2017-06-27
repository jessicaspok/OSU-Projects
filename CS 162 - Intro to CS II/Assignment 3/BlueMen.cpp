/*********************************************************************
** Program Filename: BlueMen.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: BlueMen subclass implementation file
** Input: value of attack_damage from opponent
** Output: returns attack_damage from Blue Men
*********************************************************************/

#include "BlueMen.h"

/*********************************************************************
** Function: default constructor
** Description: creates Blue Men object, sets armor, strength, and
**	name to 3, 12, The Blue Men respectively
** Paramters: None
*********************************************************************/
BlueMen::BlueMen()
{
	six_sided_die = new Die(6);
	ten_sided_die = new Die(10);
	setArmor(3);
	setStrength(12);
	setName("The Blue Men");
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
	/* 2d10 attack */
	int attack_damage = ten_sided_die->roll() + ten_sided_die->roll();
	cout << "The Blue Men's attack:   " << attack_damage << endl;
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
void BlueMen::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{  
		cout << "The Blue Men have been turned to stone!" << endl;
		strength = 0;
	}
	else 
	{
		int damage = 0;
		int defense = 0;

		/* mob defense - for every 4 points of damage, lose 1 defense die*/
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
		
		cout << "The Blue Men's defense: " << defense << endl;

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

		cout << endl << "The Blue Men are left with " << strength << " strength points."
			<< endl << endl;
	}
}