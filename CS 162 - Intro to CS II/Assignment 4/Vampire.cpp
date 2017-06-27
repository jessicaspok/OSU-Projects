/****************************************************************************************
** Class: Vampire.cpp
** Author: Jessica Spokoyny
** Date: 02/28/162-28-16
** Description: Derived from Creature. Suave. Debonair. But vicious and surprisingly
**              resilient!
****************************************************************************************/

#include "Vampire.hpp"
#include <cstdlib>

/*********************************************************************
** Function: constructor
** Description: creates vampire object, sets armor, strength, and
**	name to 1, 18, The Vampire respectively
** Paramters: None
*********************************************************************/
Vampire::Vampire(string n, bool s)
{
	six_sided_die = new Die(6);
	twelve_sided_die = new Die(12); 
	setArmor(1);
	setstrength(18);
	setPoints(0);
	setName(n);
	setType("The Vampire");
	setShowData(s);
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

	if (showData)
	{
		cout << "The Vampire " << name << "'s attack: " << attack_damage << endl;
	}
	
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
int Vampire::defend(int attack_damage)
{
	/* vampire charm: each attack has 50% chance of not occurring */
	int charm = rand() % 2;

	if (charm)
	{
		cout << "The Vampire " << name << " charmed the opponent into not attacking!"
			<< endl << endl;
		return 0;
	}

	/* medusa glare attack */
	else if (attack_damage == 99)
	{  
		if (showData)
		{
			cout << "The Vampire " << name << " has been turned to stone!" << endl;
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
void Vampire::recover()
{
	int life = strength + 9;

	if (life > 18)
	{
		strength = 18;
	}

	else
	{
		strength = life;
	}
}