#include "Hero.h"
#include "JSON.h"
#include <cmath>

Hero Hero::parse(const std::string& filename) {
	JSON file = JSON::parseFromFile(filename);
	return Hero(
		file.get<std::string>("name"),
		file.get<int>("base_health_points"),
		file.get<int>("base_damage"),
		file.get<double>("base_attack_cooldown"),
		file.get<int>("experience_per_level"),
		file.get<int>("health_point_bonus_per_level"),
		file.get<int>("damage_bonus_per_level"),
		file.get<double>("cooldown_multiplier_per_level")
	);
}

void Hero::attack(Monster& enemy) {
	if (isAlive() && canHit()) {
		if (enemy.getHealthPoints() >= damage) {
			exp += damage;
		}
		else {
			exp += enemy.getHealthPoints();
		}
		take_dmg(enemy, damage);
		while (exp >= experiencePerLevel) {
			levelUP();
		}
		resetCooldown();
	}
}

void Hero::fightTilDeath(Monster& enemy) {
	while (isAlive() && enemy.isAlive()) {
		attack(enemy);
		enemy.attack(*this);
		elapseTime(*this, 0.1);
		elapseTime(enemy, 0.1);
	}
}



void Hero::levelUP()
{
	level += 1;
	exp -= experiencePerLevel;
	baseHealthPoints += healthPointBonusPerLevel;
	healthPoints = baseHealthPoints;
	damage += damageBonusPerLevel;
	attackCooldown *= cooldownMultiplierPerLevel;
	
}
/*ezt átalakítani fighttildeath függvénnyé*/
void Hero::duel(Monster &enemy)
{
	bool can_attack = true;

	double aCD = this->getAttackCooldown();
	double bCD = enemy.getAttackCooldown();

	double rest_a = 0;
	double rest_b = 0;

	this->deal_dmg(enemy,this->getDamage());
	this->take_dmg(enemy,enemy.getDamage());

	while (this->getHealthPoints() != 0 && enemy.getHealthPoints() != 0)
	{
		if (aCD + rest_a < bCD + rest_b) {
			rest_a += aCD;
			this->deal_dmg(enemy, this->getDamage());
		}
		else if (aCD + rest_a > bCD + rest_b) {
			rest_b += bCD;
			this->take_dmg(enemy, enemy.getDamage());
		}
		else {
			rest_a += aCD;
			this->deal_dmg(enemy, this->getDamage());
		}
	}

}
