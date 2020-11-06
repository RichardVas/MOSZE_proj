#include "Fighter.h"

void Fighter::take_dmg(Fighter& enemy) {
	HP -= enemy.getDMG();
	if (HP < 0)
		HP = 0;
	enemy.exp += enemy.getDMG();

	/*level trigger*/
	if (enemy.exp >= 100)
	{
		int u = int(enemy.exp / 100);
		enemy.level += u;
		enemy.exp = enemy.exp % 100;

		for (int l = 0; l != u; ++l)
			enemy.levelUP();

	}
}

void Fighter::deal_dmg(Fighter &enemy) {
	enemy.take_dmg(*this);
}

void Fighter::levelUP()
{
	MaxHP *= 1.1;
	MaxHP = std::round(MaxHP);
	HP = MaxHP;
	DMG *= 1.1;
	DMG = std::round(DMG);
	attackcooldown *= 0.9;
}

Fighter& Fighter::duel(Fighter *enemy)
{
	bool can_attack = true;

	double aCD = this->getCD();
	double bCD = enemy->getCD();

	double rest_a = 0;
	double rest_b = 0;

	this->deal_dmg(*enemy);
	this->take_dmg(*enemy);

	while (this->getHP() != 0 && enemy->getHP() != 0)
	{
		if (aCD + rest_a < bCD + rest_b) {
			rest_a += aCD;
			this->deal_dmg(*enemy);
		}
		else if (aCD + rest_a > bCD + rest_b) {
			rest_b += bCD;
			this->take_dmg(*enemy);
		}
		else {
			rest_a += aCD;
			this->deal_dmg(*enemy);
		}
	}
	if (this->getHP() > enemy->getHP())
	{
		return *this;
	}
	else
	{
		return *enemy;
	}

}

std::ostream& operator<<(std::ostream& os, Fighter& fi)
{
	os << fi.getName() << ": HP: " << fi.getHP() << "," << " DMG: " << fi.getDMG() << std::endl;
	return os;
}


