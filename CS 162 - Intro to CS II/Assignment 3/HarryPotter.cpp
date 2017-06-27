/*********************************************************************
** Program Filename: HarryPotter.cpp
** Author: Jessica Spokoyny
** Date: 02/14/16
** Description: HarryPotter subclass implementation file
** Input: value of attack_damage from opponent, bool variable for 
**	hogwarts
** Output: returns attack_damage from harry potter, bool variable for
**	hogwarts
*********************************************************************/

#include "HarryPotter.h"

/*********************************************************************
** Function: default constructor
** Description: creates harry potter object, sets armor, strength, and
**	name to 1, 10, Harry Potter respectively
** Paramters: None
*********************************************************************/
HarryPotter::HarryPotter()
{
	six_sided_die = new Die(6);
	setArmor(0);
	setStrength(10);
	setName("Harry Potter");
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
	/* 2d6 attack */
	int attack_damage = six_sided_die->roll() + six_sided_die->roll();
	cout << "Harry Potter's attack: " << attack_damage << endl;
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
void HarryPotter::defend(int attack_damage)
{
	/* medusa glare attack */
	if (attack_damage == 99)
	{  
		cout << "Harry Potter has been turned to stone!" << endl;
		strength = 0;
	}
	else 
	{
		int damage = 0;
		int defense = 0;

		/* 2d6 defense + armor */
		defense = six_sided_die->roll() + six_sided_die->roll() + armor;
		cout << "Harry Potter's defense: " << defense << endl;

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

		/* hogwarts defense: if harry dies, he immediately recovers to strength of 20 */
		/* this power can only be used once so must be checked with bool */
		if ((strength == 0) && (hogwarts == true))
		{
			cout << "Harry died, but used his Hogwarts power to recover." << endl;
			setStrength(20);
			setHogwarts(false);
		}

		cout << endl << "Harry Potter is left with " << strength << " strength points."
			<< endl << endl;
	}
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
