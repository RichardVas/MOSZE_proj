#pragma once

#include "Monster.h"


class Hero : public Monster {

	double baseHealthPoints;            
	double experiencePerLevel;          
	double experienceState ;              
	double healthPointBonusPerLevel;     
	double damageBonusPerLevel;          
	double cooldownMultiplierPerLevel;   

	double level;                        

public:

	Hero() {}


	Hero(const std::string& name, const double& healthPoints, const double& damage, const double& attackCooldown, const double& experiencePerLevel,
		const double& healthPointBonusPerLevel, const double& damageBonusPerLevel, const double& cooldownMultiplierPerLevel) :
		Monster(name, healthPoints, damage, attackCooldown), baseHealthPoints(healthPoints), experiencePerLevel(experiencePerLevel),
		experienceState(0), healthPointBonusPerLevel(healthPointBonusPerLevel), damageBonusPerLevel(damageBonusPerLevel),
		cooldownMultiplierPerLevel(cooldownMultiplierPerLevel), level(1) {}



	static Hero parse(const std::string& filename);


	void attack(Monster& enemy);


	void fightTilDeath(Monster& enemy);

	
	double getMaxHealthPoints() const { return baseHealthPoints; }

	
	double getLevel() const { return level; }
};

