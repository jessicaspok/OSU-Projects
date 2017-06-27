/*********************************************************************
** Program Filename: HarryPotter.cpp
** Author: Jessica Spokoyny
** Date: 02/28/16
** Description: HarryPotter subclass implementation file
** Input: value of attack_damage from opponent, bool variable for
**	hogwarts
** Output: returns attack_damage from harry potter, bool variable for
**	hogwarts
*********************************************************************/

#include "HarryPotter.hpp"

/*********************************************************************
** Function: constructor
** Description: creates harry potter object, sets armor, strength, and
**	name to 1, 10, Harry Potter respectively
** Paramters: None
*********************************************************************/
HarryPotter::HarryPotter(string n, bool s)
{
	six_sided_die = new Die(6);
	setArmor(0);
	setstrength(10);
	setPoints(0);
	setName(n);
	setType("Harry Potter");
	setShowData(s);
	setHogwarts(true);
}

/*********************************************************************
** Function: destructor
** Description: deletes 6-sided die created for harry potter to roll
** Paramters: None
*********************************************************************/
HarryPotter::~HarryPotter()
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
int HarryPotter::attack()
{
	int attack_damage = six_sided_die->roll() + six_sided_die->roll();
	
	if (showData)
	{
		cout << "Harry Potter " << name << "'s attack: " << attack_damage << endl;
	}
	
	return attack_damage;
}

/*********************************************************************
** Function: defend
** Description: calculates and returns defense value after rolling 2
**	6-sided die and adding armor. also checks whether harry potter is
**	dead or should continue to next round and if medusa glared
** Parameters: value of incoming attack from other player
** Pre-Conditions: the int passed is valid
** Post-Conditions: returns result of combat and adjusts strength
*********************************************************************/
int HarryPotter::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{ 
		if (showData)
		{
			cout << "Harry Potter " << name << " has been turned to stone!" << endl;
		}

		strength = 0;
		return 20;
	}

	else 
	{
		int defense = six_sided_die->roll() + six_sided_die->roll() + armor;
		int p1pts = defensePrint(name, type, attack_damage, defense);

		if ((strength == 0) && (hogwarts == true))
		{
			if (showData)
			{
				cout << "Harry Potter " << name << " died, but used his Hogwarts power to recover." << endl;
			}

			setstrength(20);
			setHogwarts(false);
		}

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
void HarryPotter::recover()
{
	int life = strength + 5;
	if (life > 10)
	{
		strength = 10;
	}

	else
	{
		strength = life;
	}

	/* reset hogwarts bool */
	hogwarts = true;
}

/*********************************************************************
** Function: getHogwarts
** Description: retruns hogwarts bool value
** Parameters: none
*********************************************************************/
bool HarryPotter::getHogwarts()
{
	return hogwarts;
}

/*********************************************************************
** Function: setHogwarts
** Description: set hogwarts bool value
** Parameters: bool value
*********************************************************************/
void HarryPotter::setHogwarts(bool h)
{
	this->hogwarts = h;
}
