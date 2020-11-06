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
			experienceState += damage;
		}
		else {
			experienceState += enemy.getHealthPoints();
		}
		sufferDamage(enemy, damage);
		while (experienceState >= experiencePerLevel) {
			level += 1;
			experienceState -= experiencePerLevel;
			baseHealthPoints += healthPointBonusPerLevel;
			healthPoints = baseHealthPoints;
			damage += damageBonusPerLevel;
			attackCooldown *= cooldownMultiplierPerLevel;
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
